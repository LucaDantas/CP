#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

#define pb push_back
#define ff first
#define ss second

constexpr int maxn = 3e5+10, logn = 20;

int pai[maxn][logn], depth[maxn], passando_pai[maxn], passando_mim[maxn], cnt[maxn], qtd[maxn];

map<pii, int> mp;

pii filhos[maxn];

vector<int> g[maxn], termina[maxn];

void init(int u) {
	for(int v : g[u]) {
		if(v != pai[u][0]) {
			depth[v] = depth[u]+1;
			pai[v][0] = u;
			init(v);
		}
	}
}

tiii lca(int a, int b) {
	if(a == b) return {-1, -1, a};
	if(depth[a] < depth[b])
		swap(a, b);
	for(int l = logn-1; l >= 0; l--)
		if(depth[a] - (1 << l) > depth[b])
			a = pai[a][l];
	if(pai[a][0] == b) return {a, -1, pai[a][0]};
	if(depth[a] != depth[b])
		a = pai[a][0];
	for(int l = logn-1; l >= 0; l--)
		if(pai[a][l] != pai[b][l])
			a = pai[a][l], b = pai[b][l];
	assert(a != b && pai[a][0] == pai[b][0]);
	return {a, b, pai[a][0]};
}

long long ans = 0;

void dfs(int u, int p) {
	for(int v : g[u]) {
		if(v != p) {
			dfs(v, u);
			passando_pai[u] += passando_pai[v];
			passando_mim[u] += passando_mim[v];
		}
	}
	ans += 1ll * qtd[u] * passando_mim[u];
	ans += 1ll * qtd[u] * (qtd[u]-1) / 2;
	long long remover = 0;
	for(int x : termina[u]) {
		auto [f1, f2] = filhos[x];
		if(f1 != -1)
			remover += cnt[f1] - 1, ans -= passando_pai[f1];
		if(f2 != -1)
			remover += cnt[f2] - 1, ans -= passando_pai[f2];
		if(f1 != -1 && f2 != -1)
			remover -= mp[{f1, f2}] - 1;
	}
	ans -= remover / 2;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	init(1);
	for(int l = 1; l < logn; l++)
		for(int i = 1; i <= n; i++)
			pai[i][l] = pai[pai[i][l-1]][l-1];
	int m; scanf("%d", &m);
	for(int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		if(depth[a] < depth[b])
			swap(a, b);
		auto [p1, p2, l] = lca(a, b);
		++qtd[l];
		termina[l].pb(i);
		if(p1 < p2) swap(p1, p2);
		filhos[i] = {p1, p2};
		if(p1 != -1) ++cnt[p1];
		if(p2 != -1) ++cnt[p2];
		if(p1 != -1 && p2 != -1)
			++mp[{p1, p2}];
		if(p1 != -1)
			++passando_pai[a], --passando_pai[p1];
		if(p2 != -1)
			++passando_pai[b], --passando_pai[p2];
		++passando_mim[a], ++passando_mim[b];
		passando_mim[l] -= 2;
	}
	dfs(1, 0);
	printf("%lld\n", ans);
}