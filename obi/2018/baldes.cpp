#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

int val[maxn][2];

struct SegmentTree
{
	int k; pii tree[4*maxn];
	SegmentTree(int _k) : k(_k) {}
	inline bool opa(int a, int b) {return k?a>b:a<b;}
	inline int op(int a, int b) {return opa(val[a][k], val[b][k])?a:b;}
	pii comp(pii a, pii b) {
		pii ans = {-1, -1};
		ans.ff = op(a.ff, b.ff);
		if(ans.ff == a.ff)
			a.ff = a.ss;
		else b.ff = b.ss;
		ans.ss = op(a.ff, b.ff);
		return ans;
	}
	void build(int node, int i, int j) {
		if(i == j)
			return (void)(tree[node] = {i, 0});
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = comp(tree[2*node], tree[2*node+1]);
	}
	void upd(int node, int i, int j, int pos) {
		if(i == j) return;
		int m = (i+j) >> 1;
		if(pos <= m) upd(2*node, i, m, pos);
		else upd(2*node+1, m+1, j, pos);
		tree[node] = comp(tree[2*node], tree[2*node+1]);
	}
	pii query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return {0, 0};
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return comp(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}
} seg0(0), seg1(1);

int main() {
	int n, m; scanf("%d %d", &n, &m);
	val[0][1] = 0; val[0][0] = inf;
	for(int i = 1; i <= n; i++)
		scanf("%d", &val[i][0]), val[i][1] = val[i][0];

	seg0.build(1, 1, n);
	seg1.build(1, 1, n);

	while(m--) {
		int t, x, y; scanf("%d %d %d", &t, &x, &y);
		if(t == 1) {
			if(x < val[y][0])
				val[y][0] = x, seg0.upd(1, 1, n, y);
			if(x > val[y][1])
				val[y][1] = x, seg1.upd(1, 1, n, y);
		} else {
			pii mn = seg0.query(1, 1, n, x, y);
			pii mx = seg1.query(1, 1, n, x, y);
			if(mn.ff != mx.ff) printf("%d\n", val[mx.ff][1] - val[mn.ff][0]);
			else printf("%d\n", max(val[mx.ss][1] - val[mn.ff][0], val[mx.ff][1] - val[mn.ss][0]));
		}
	}
}