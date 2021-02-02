#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 2e5+10, logn = 20, mod = 1e9+7;

vector<int> g[maxn], g2[maxn], grp[maxn];

int pai[maxn][logn+1], in[maxn], depth[maxn], t;

void add(int& a, int b) {a += b; if(a >= mod) a -= mod;}

void dfs(int u, int p, int d) {
	in[u] = ++t;
	depth[u] = d;
	grp[d].pb(u);
	for(int v : g[u])
		if(v != p)
			dfs(v, u, d+1);
}

int lca(int a, int b) {
	if(depth[a] < depth[b])
		swap(a, b);
	for(int l = logn; l >= 0; l--)
		if(depth[a] - (1 << l) >= depth[b])
			a = pai[a][l];
	if(a == b) return a;
	for(int l = logn; l >= 0; l--)
		if(pai[a][l] != pai[b][l])
			a = pai[a][l], b = pai[b][l];
	return pai[a][0];
}

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * b * ans % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

pii dp[maxn];
int tam[maxn], pot[maxn];

#define inv(a) power(a, mod-2)

void dfs2(int u) {
	if(!g2[u].size())
		return (void)(dp[u] = {1, 1}, tam[u] = 1);
	dp[u] = {0, 0};
	tam[u] = 0;
	vector<pii> a;
	int errado = 1;
	for(int v : g2[u]) {
		dfs2(v);
		tam[u] += tam[v];
		errado = (int)(1ll * errado * dp[v].ss % mod);
		a.pb(dp[v]);
	}
	for(pii x : a)
		add(dp[u].ff, (int)(1ll * x.ff * (1ll * errado * inv(x.ss) % mod) % mod));
	dp[u].ss = (pot[tam[u]] - dp[u].ff + mod) % mod;
}

int main() {
	int n; scanf("%d", &n); ++n;
	for(int i = 2; i <= n; i++)
		scanf("%d", &pai[i][0]), ++pai[i][0], g[pai[i][0]].pb(i);
	dfs(1, 0, 0);

	for(int i = 1; i <= n; i++)
		for(int l = 1; l <= logn; l++)
			pai[i][l] = pai[pai[i][l-1]][l-1];

	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = 2*pot[i-1]%mod;

	int ans = 0;
	for(int i = 0; grp[i].size(); i++) {
		sort(grp[i].begin(), grp[i].end(), [](int a, int b){return in[a]<in[b];});
		vector<int> a = {grp[i][0]};
		for(int j = 1; j < (int)grp[i].size(); j++) {
			a.pb(lca(grp[i][j], grp[i][j-1]));
			a.pb(grp[i][j]);
		}
		sort(a.begin(), a.end(), [](int x, int y){return in[x]<in[y];});
		a.resize(unique(a.begin(), a.end()) - a.begin());

		for(int x : a)
			g2[x].clear();

		for(int j = 1; j < (int)a.size(); j++)
			g2[lca(a[j], a[j-1])].pb(a[j]);

		dfs2(a[0]);
		add(ans, (int)(1ll * dp[a[0]].ff * pot[n - (int)grp[i].size()] % mod));
	}
	printf("%d\n", ans);
}