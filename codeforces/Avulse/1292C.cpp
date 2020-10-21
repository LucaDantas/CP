#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 3e3+10;

vector<int> g[maxn];

long long dp[maxn][maxn];
int prox[maxn][maxn], sz[maxn], depth[maxn], pai[maxn], n;

vector<int> dfs(int u, int p) {
	depth[u] = depth[p]+1;
	pai[u] = p;
	vector<int> here;
	for(int v : g[u]) {
		if(v != p) {
			vector<int> vai = dfs(v, u);
			for(int x : vai)
				prox[u][x] = v, here.pb(x);
			sz[u] += sz[v];
		}
	}
	sz[u]++;
	here.pb(u);
	return here;
}

long long solve(int u, int v) {
	if(u == v) return 0;
	if(depth[u] > depth[v])
		swap(u, v);
	if(dp[u][v] != -1) return dp[u][v];
	if(prox[u][v])
		return dp[u][v] = max(solve(prox[u][v], v), solve(u, pai[v]))
			+ 1ll * sz[v] * (n - sz[prox[u][v]]);
	return dp[u][v] = max(solve(pai[u], v), solve(u, pai[v])) + 1ll * sz[u] * sz[v];
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1, 0);
	memset(dp, -1, sizeof dp);
	long long ans = 0;
	for(int u = 1; u <= n; u++)
		for(int v = u+1; v <= n; v++)
			ans = max(ans, solve(u, v));
	printf("%lld\n", ans);
}