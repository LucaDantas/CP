#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

int n;

struct SegmentTree {
	int tree[maxn<<2], lazy[maxn<<2], a[maxn];
	
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;

		if(i != j) lazy[node<<1] += lazy[node], lazy[node<<1|1] += lazy[node];

		tree[node] += lazy[node]; lazy[node] = 0;
	}

	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(node<<1, i, m); build(node<<1|1, m+1, j);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	
	void upd(int node, int i, int j, int l, int r, int v) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(lazy[node] += v, flush(node, i, j));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, v);
		upd(node<<1|1, m+1, j, l, r, v);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	
	int query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l) return inf;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return min(query(node<<1, i, m, l, r), query(node<<1|1, m+1, j, l, r));
	}
} seg;

int b[maxn], a[maxn], p[maxn], f[maxn]; // b é quanto precisa, a é quanto tem disponivel

int val[maxn], desce[maxn];

set<int> extra;

vector<pair<int,int>> rmv;

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d %d", &b[i], &a[i], &p[i]);
		val[i] = (i ? val[i-1] : 0) + a[i] - b[i];
		if(val[i] < 0) return puts("-1"), 0;
		if(val[i] > a[i]) extra.insert(i), desce[i] = val[i] - a[i], val[i] = a[i];
		seg.a[i] = val[i];
		
		rmv.push_back({p[i], i});
	}
	seg.build(1, 0, n-1);
	extra.insert(n); desce[n] = inf;
		
	sort(rmv.begin(), rmv.end()); reverse(rmv.begin(), rmv.end());
	for(int i = 0; i < n; i++) {
		int v = rmv[i].first, pos = rmv[i].second;
		for(auto it = extra.upper_bound(pos);; it = extra.erase(it)) {
			int mn = min({a[pos], seg.query(1, 0, n-1, pos, *it-1), desce[*it]});
			a[pos] -= mn; // diminuo a quantidade de caras q eu to comprando
			seg.upd(1, 0, n-1, pos, (*it)-1, -mn);
			desce[*it] -= mn;
			if(desce[*it] > 0) break;
		}
	}
	long long custo = 0;
	for(int i = 0; i < n; i++)
		custo += a[i] * p[i];
	printf("%lld\n", custo);
}
