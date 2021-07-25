#include "candies.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int n;

struct SegmentTree {
	long long tree[maxn<<2][2], lazy[maxn<<2];
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j) lazy[node<<1] += lazy[node], lazy[node<<1|1] += lazy[node];
		tree[node][0] += lazy[node]; tree[node][1] += lazy[node]; lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, long long v) {
		flush(node, i, j);
		if(j < l) return;
		if(i >= l) return (void)(lazy[node] += v, flush(node, i, j));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, v); upd(node<<1|1, m+1, j, l, v);
		tree[node][0] = min(tree[node<<1][0], tree[node<<1|1][0]);
		tree[node][1] = max(tree[node<<1][1], tree[node<<1|1][1]);
	}
	void upd(int l, long long v) { upd(1, 0, n-1, l, v); }
	long long mn(int node, int i, int j, int l) {
		flush(node, i, j);
		if(j < l) return inf;
		if(i >= l) return tree[node][0];
		int m = (i+j) >> 1;
		return min(mn(node<<1, i, m, l), mn(node<<1|1, m+1, j, l));
	}
	long long mn(int l) { return mn(1, 0, n-1, l); }
	long long mx(int node, int i, int j, int l) {
		flush(node, i, j);
		if(j < l) return -inf;
		if(i >= l) return tree[node][1];
		int m = (i+j) >> 1;
		return max(mx(node<<1, i, m, l), mx(node<<1|1, m+1, j, l));
	}
	long long mx(int l) { return mx(1, 0, n-1, l); }
	int last(int node, int i, int j, long long val) {
		flush(node, i, j);
		if(tree[node][1] < val) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int p1 = last(node<<1|1, m+1, j, val);
		if(p1 != -1) return p1;
		return last(node<<1, i, m, val);
	}
	int last(long long val) { return last(1, 0, n-1, val); }
	long long ultimo(int node = 1, int i = 0) {
		flush(node, i, n-1);
		if(i == n-1) return tree[node][1];
		int m = (i+n-1) >> 1;
		return ultimo(node<<1|1, m+1);
	}
	void deb(int node, int i, int j) {
		flush(node, i, j);
		if(i == j) return (void)(fprintf(stderr, "%lld ", tree[node][0]));
		int m = (i+j) >> 1;
		deb(node<<1, i, m); deb(node<<1|1, m+1, j);
	}
} seg;

int get(int c) {
	int l = 0, r = n-1;
	long long ans = 0;
	while(l <= r) {
		int m = (l+r) >> 1;
		long long mx = seg.mx(m);
		if(mx <= c) { r = m-1; continue; }
		int pos = seg.last(mx);
		long long mn = seg.mn(pos);
		if(mx - c >= mn) ans = max(ans, mn), l = m+1;
		else ans = max(ans, mx-c), r = m-1;
	}
	return (int)(seg.ultimo() - ans);
}

vector<int> ans, C;

// Tipo conectividade dinamica (seg de tempo e depois faz a dfs com rollback)
struct Seg2 {
	vector<pair<int,int>> tree[maxn<<2];
	void upd(int node, int i, int j, int l, int r, int t, int v) {
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(tree[node].push_back({t, v}));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, t, v); upd(node<<1|1, m+1, j, l, r, t, v);
	}
	void go(int node, int i, int j) {
		for(auto [t, v] : tree[node])
			seg.upd(t, v);
		long long mn = seg.mn(0);
		if(mn < 0 && i == j) seg.upd(0, -mn);

		int m = (i+j) >> 1;
		if(i == j) ans[i] = get(C[i]);
		else go(node<<1, i, m), go(node<<1|1, m+1, j);
		
		if(mn < 0 && i == j) seg.upd(0, mn);
		for(auto [t, v] : tree[node])
			seg.upd(t, -v);
	}
} seg2;

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) {
	n = (int)(v.size()); ans.resize(c.size());
	C = c;

	int m = (int)(c.size());
	for(int i = 0; i < n; i++)
		seg2.upd(1, 0, m-1, l[i], r[i], i, v[i]);

	seg2.go(1, 0, m-1);

	return ans;
}
