#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, inf = 0x3f3f3f3f;

vector<pair<int,int>> g[maxn];

int dp[maxn][2]; // posso retornar com o pai livre ou sem o pai livre

void dfs(int u, int p, int peso_pai) {
	for(auto [v, w] : g[u]) if(v != p) {
		dfs(v, u, w);
		dp[u][1] = max(dp[u][1], dp[v][0] + w + peso_pai - max(dp[v][0], dp[v][1]));
		dp[u][0] += max(dp[v][0], dp[v][1]);
	}
	dp[u][1] += dp[u][0];
}

int ans;

void reroot(int u, int p) {
	int sv0 = dp[u][0], sv1 = dp[u][1]; // dou roolback no final

	int sz = (int)(g[u].size());
	vector<array<int,2>> pref(sz+1, array<int,2>({0, -inf})), suf(sz+1, array<int,2>({0, -inf}));
	
	for(int i = 0; i < sz; i++) {
		auto [v, w] = g[u][i];
		pref[i][1] = max(i ? pref[i-1][1] : -inf, dp[v][0] + w - max(dp[v][0], dp[v][1])); // tem que adicionar o peso_pai aqui
		pref[i][0] = (i ? pref[i-1][0] : 0) + max(dp[v][0], dp[v][1]);
	}

	for(int i = sz-1; i >= 0; i--) {
		auto [v, w] = g[u][i];
		suf[i][1] = max(suf[i+1][1], dp[v][0] + w - max(dp[v][0], dp[v][1])); // tem que adicionar o peso_pai aqui
		suf[i][0] = suf[i+1][0] + max(dp[v][0], dp[v][1]);
	}

	ans = max(ans, suf[0][0]);

	for(int i = 0; i < sz; i++) {
		if(g[u][i].first == p) continue;

		dp[u][0] = (i ? pref[i-1][0] : 0) + suf[i+1][0];
		
		dp[u][1] = dp[u][0] + max((i ? pref[i-1][1] : -inf), suf[i+1][1]) + (sz > 1 ? g[u][i].second : 0);

		reroot(g[u][i].first, u);
	}

	dp[u][0] = sv0, dp[u][1] = sv1;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b, w; i < n; i++)
		scanf("%d %d %d", &a, &b, &w), g[a].push_back({b, w}), g[b].push_back({a, w});
	dfs(1, 0, 0);
	reroot(1, 0);
	printf("%d\n", ans);
}
