#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2010;
constexpr int mod = 1e9+7;

int a[maxn], dp[maxn], d;

vector<int> g[maxn];

void dfs(int u, int p, int menor, int id) {
	dp[u] = 1;
	for(auto v : g[u]) {
		if(v != p && (a[v] > menor || (a[v] == menor && v < id)) && a[v]-menor <= d) {
			dfs(v, u, menor, id);
			dp[u] += (int)(1ll * dp[u] * dp[v] % mod);
			if(dp[u] >= mod) dp[u] -= mod;
		}
	}
}

int main() {
	int n, ans = 0; scanf("%d %d", &d, &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d %d", &u, &v);
		g[u-1].pb(v-1);
		g[v-1].pb(u-1);
	}
	for(int i = 0; i < n; i++) {
		dfs(i, -1, a[i], i);
		ans += dp[i];
		if(ans >= mod) ans -= mod;
	}
	printf("%d\n", ans);
}