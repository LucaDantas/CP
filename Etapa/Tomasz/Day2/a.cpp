#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
	void itv(int l, int r, int v) { upd(l, v); upd(r, -v); }
} bit;

int in[maxn], out[maxn], t;

vector<int> g[maxn];

void dfs(int u) {
	in[u] = ++t;
	for(int v : g[u])
		if(!in[v]) dfs(v);
	out[u] = ++t;
}

struct Edge {
	int a, b, c;
} edges[maxn];

int main() {
	int n, m, q; scanf("%d %d %d", &n, &m, &q);
	for(int i = 1, a, b, c; i < n; i++)
		scanf("%d %d %d", &a, &b, &c), g[a].pb(b), g[b].pb(a), edges[i] = {a, b, c};
	dfs(1);
	for(int i = 1; i < n; i++) {
		if(in[edges[i].a] < in[edges[i].b])
			swap(edges[i].a, edges[i].b);
		add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
	}

	for(int i = 1; i <= n; i++)
		printf("%d -> %d %d\n", i, in[i], out[i]);

	while(q--) {
		char c; scanf(" %c", &c);
		if(c == 'Z') {
			int u; scanf("%d", &u);
			printf("%d\n", bit.query(in[u]));
		} else {
			int i, val; scanf("%d %d", &i, &val);
			rmv(edges[i].c, {in[edges[i].a], out[edges[i].a]});
			edges[i].c = val;
			add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
		}
	}
}