#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 3e5+10;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
	int sz(int a) { return peso[find(a)]; }
	void add_sz(int a) { ++peso[find(a)]; }
} dsu;

int n, m;

vector<int> g[maxn];

int mark[2*maxn], low[maxn], depth[maxn], qtd = 0;

vector<int> cut[maxn], tree[2*maxn];

vector<int> here;

void dfs1(int u) {
	++qtd;
	mark[u] = 1;
	here.pb(u);
	for(int v : g[u]) {
		if(mark[v]) low[u] = min(low[u], depth[v]);
		else {
			depth[v] = depth[u] + 1;
			dfs1(v);
			low[u] = min(low[u], low[v]);
			if(low[v] < depth[u]) dsu.join(u, v);
			else cut[u].pb(dsu.find(v));
		}
	}
}

void dfs2(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(!mark[v]) dfs2(v);
	if(!cut[u].size()) return;
	int fam = dsu.find(u);
	if(u != 1) {
		tree[u+n].pb(fam);
		tree[fam].pb(u+n);
	}
	for(int v : cut[u]) {
		dsu.add_sz(v);
		tree[u+n].pb(v);
		tree[v].pb(u+n);
	}
}

long long ans = 0, dp[maxn]; // maneira de escolher 2 na msm subtree

int sz[maxn];

void rotate(int u, int v) {
	sz[u] -= sz[v];
	sz[v] += sz[u];
	if(u > n) {
		// u => cut, v => block
		dp[u] = (long long)sz[u] * (sz[u] - 1);
		dp[v] += dp[u];
	} else {
		dp[u] -= dp[v];
		dp[v] = (long long)sz[v] * (sz[v] - 1);
	}
}

void dfs4(int u, int p) {
	sz[u] += u<=n?dsu.sz(u)-(int)tree[u].size():1;
	for(int v : tree[u]) {
		if(v == p) continue;
		dfs4(v, u);
		sz[u] += sz[v];
		if(u<=n) dp[u] += dp[v];
	}
	if(u > n) dp[u] = (long long)sz[u] * (sz[u] - 1);
}

void dfs3(int u, int p) {
	bool b = u<=n?1:0; // 1 -> block, 0 -> cut
	if(b) {
		int tam = dsu.sz(u) - (int)tree[u].size();
		for(int v : tree[u])
			ans -= 1ll * tam * dp[v];
		for(int v : tree[u]) {
			if(v != p) {
				rotate(u, v);
				dfs3(v, u);
				rotate(v, u);
			}
		}
	} else {
		mark[u] = 1;
		for(int v : tree[u])
			ans -= dp[v];
		for(int v : tree[u]) {
			if(v != p) {
				rotate(u, v);
				dfs3(v, u);
				rotate(v, u);
			}
		}
	}
}

void root(int u) {
	mark[u] = 1; here = {u}; ++qtd;
	for(int v : g[u])
		if(!mark[v]) depth[v] = 1, dfs1(v), cut[u].pb(dsu.find(v));
	if(cut[u].size() == 1)
		dsu.join(cut[u][0], u), cut[u].clear();
	for(int x : here)
		mark[x] = 0;
	dfs2(u); // comeco a dp no meu block
	for(int x : here)
		mark[x] = 1;
	here.clear();
}

void root_ans(int u) {
	dfs4(u, 0);
	dfs3(u, 0);
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	for(int i = 0; i < maxn; i++)
		low[i] = maxn;
	auto choose3 = [](int a) {
		if(a < 3) return 0ll;
		return (1ll * a * (a-1) * (a-2));
	};
	for(int i = 1; i <= n; i++)
		if(!mark[i]) root(i), ans += choose3(qtd), qtd = 0;
	for(int i = n+1; i <= 2*n; i++)
		if(!mark[i] && tree[i].size()) root_ans(i);
	printf("%lld\n", ans);
}