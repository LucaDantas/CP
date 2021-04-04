#include <cstdio>
#include <vector>

constexpr int maxn = 5e3+10, mod = 998244353;

std::vector<int> g[maxn];

int dp[maxn][maxn], new_dp[maxn][maxn], sz[maxn], k;

void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }
int max(int a, int b) { return a > b ? a : b; }

void dfs(int u, int p) {
	sz[u] = 1; dp[u][0] = 1;
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);

		// Possibilidades juntando
		for(int i = sz[u]-1; i >= 0; i--)
			for(int j = 0; j < sz[v] && i + j + 1 <= k; j++)
				add(new_dp[u][max(i, j+1)],
					(int)(1ll * dp[u][i] * dp[v][j] % mod));

		// Possibilidades sem juntar
		int sum = 0;
		for(int j = 0; j <= sz[v]-1; j++)
			add(sum, dp[v][j]);

		for(int i = sz[u]-1; i >= 0; i--)
			dp[u][i] = (int)(1ll * sum * dp[u][i] % mod);

		sz[u] = max(sz[u], sz[v]+1);
		for(int i = sz[u]-1; i >= 0; i--) {
			add(dp[u][i], new_dp[u][i]);
			new_dp[u][i] = 0;
		}
	}
}

int main() {
	int n; scanf("%d %d", &n, &k);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	dfs(1, 0);
	int ans = 0;
	for(int i = 0; i <= k; i++)
		add(ans, dp[1][i]);
	printf("%d\n", ans);
}