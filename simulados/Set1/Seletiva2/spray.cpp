#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

struct SegmentTree
{
	long long tree[4*maxn]; int k, a[maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	void upd(int node, int i, int j, int pos, int v) {
		if(i == j) return (void)(tree[node] = v);
		int m = (i+j) >> 1;
		if(pos <= m) upd(2*node, i, m, pos, v);
		else upd(2*node+1, m+1, j, pos, v);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	void apply(int node, int i, int j, int l, int r) {
		if(i > r || j < l || !tree[node]) return;
		if(i == j) return (void)(tree[node] /= k);
		int m = (i+j) >> 1;
		apply(2*node, i, m, l, r);
		apply(2*node+1, m+1, j, l, r);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	long long query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0ll;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return query(2*node, i, m, l, r) + query(2*node+1, m+1, j, l, r);
	}
} seg;

int main() {
	int n, q, k; scanf("%d %d %d", &n, &q, &k); seg.k = k;
	for(int i = 1; i <= n; i++)
		scanf("%d", &seg.a[i]);
	seg.build(1, 1, n);
	while(q--) {
		int s, a, b; scanf("%d %d %d", &s, &a, &b);
		if(s == 1) seg.upd(1, 1, n, a, b);
		if(s == 2 && k > 1) seg.apply(1, 1, n, a, b);
		if(s == 3) printf("%lld\n", seg.query(1, 1, n, a, b));
	}
}