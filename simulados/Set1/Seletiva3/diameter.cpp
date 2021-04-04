#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

int filho[maxn], in[maxn], out[maxn], t;
long long cost[maxn];

vector<pair<int,int>> g[maxn];

void dfs(int u, int p) {
	in[u] = out[u] = ++t;
	for(auto [v, id] : g[u]) {
		if(v != p) {
			filho[id] = v;
			dfs(v, u);
			out[u] = ++t; // eu me readiciono para os meus filhos me verem
		}
	}
}

template<int N>
struct SegmentTree
{
	struct Node
	{
		long long a, b, ab, ba, aba, lazy;
		Node() {
			a = b = ab = ba = aba = lazy = 0;
		}
		Node operator+(Node other) {
			Node ret;
			ret.a = max(a, other.a);
			ret.b = max(b, other.b);
			ret.ab = max({ab, other.ab, a + other.b});
			ret.ba = max({ba, other.ba, b + other.a});
			ret.aba = max({aba, other.aba, ab + other.a, a + other.ba});
			// lazy should always be 0
			return ret;
		}
	} tree[4*N];

	void flush(int node, int i, int j) {
		if(!tree[node].lazy) return;
		long long& lz = tree[node].lazy;
		tree[node].a += lz;
		tree[node].b -= 2*lz;
		tree[node].ab -= lz;
		tree[node].ba -= lz;

		if(i != j) {
			tree[node<<1].lazy += lz;
			tree[node<<1|1].lazy += lz;
		}

		lz = 0;
	}

	void upd(int l, int r, long long v, int node = 1, int i = 1, int j = N) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) {
			tree[node].lazy = v;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(l, r, v, node<<1, i, m);
		upd(l, r, v, node<<1|1, m+1, j);

		tree[node] = tree[node<<1] + tree[node<<1|1];
	}

	long long query() { flush(1, 1, N); return tree[1].aba; }
};

SegmentTree<maxn> seg;

int main() {
	int n, q; long long w; scanf("%d %d %lld", &n, &q, &w);
	for(int i = 0; i < n-1; i++) {
		int a, b; long long c; scanf("%d %d %lld", &a, &b, &c);
		g[a].pb({b, i});
		g[b].pb({a, i});
		cost[i] = c;
	}
	dfs(1, 0);
	for(int i = 0; i < n-1; i++) {
		int u = filho[i];
		seg.upd(in[u], out[u], cost[i]);
	}
	long long last = 0;
	while(q--) {
		int d; long long e; scanf("%d %lld", &d, &e);
		d = (int)((d + last) % (n - 1));
		e = (e + last) % w;
		seg.upd(in[filho[d]], out[filho[d]], e - cost[d]);
		cost[d] = e;
		last = seg.query();
		printf("%lld\n", last);
	}
}