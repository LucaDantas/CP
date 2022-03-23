#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

int dp[maxn][maxn][2]; // dp(i, k, flag) = menor dinheiro na subarvore de i com k goods, flag == usei o cupom ou nao pro cara

int sz[maxn], c[maxn], d[maxn];

vector<int> g[maxn]; // so os filhos

void dfs(int u) {
	dp[u][0][0] = 0, dp[u][1][0] = c[u], dp[u][1][1] = c[u] - d[u];
	sz[u] = 1;
	for(int v : g[u]) {
		dfs(v);
		for(int i = sz[u]; i >= 0; i--) {
			for(int j = 1; j <= sz[v]; j++) {
				dp[u][i+j][0] = min(dp[u][i+j][0], dp[u][i][0] + dp[v][j][0]);
				dp[u][i+j][1] = min(dp[u][i+j][1], dp[u][i][1] + min(dp[v][j][0], dp[v][j][1]));
			}
		}
		sz[u] += sz[v];
	}
}

int main() {
	memset(dp, 0x3f, sizeof dp);
	int n, b; scanf("%d %d", &n, &b);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", c+i, d+i);
		if(i>=2) { int p; scanf("%d", &p); g[p].push_back(i); }
	}
	dfs(1);
	int ans = 0;
	for(int i = 0; i < maxn; i++)
		if(min(dp[1][i][0], dp[1][i][1]) <= b) ans = i;
	printf("%d\n", ans);
}
