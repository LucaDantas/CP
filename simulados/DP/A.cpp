#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>

constexpr int maxn = 3010;
constexpr unsigned int inf = 0xffffffff;

int dist[maxn][maxn], sz[maxn][maxn];
unsigned int dp[maxn][maxn];

std::vector<int> g[maxn];

void get(int u, int p, int s) {
	dist[s][u] = dist[s][p]+1;
	sz[u][s] = 1;
	for(int v : g[u])
		if(v != p) get(v, u, s), sz[u][s] += sz[v][s];
}

unsigned int dfs(int l, int r) {
	if(l > r) std::swap(l, r);
	if(dp[l][r] != inf) return dp[l][r];
	unsigned int& here = dp[l][r];
	here = sz[l][r] * sz[r][l];
	unsigned int coloco = 0;
	for(int v : g[l])
		if(dist[v][r] > dist[l][r])
			coloco = std::max(coloco, dfs(v, r));
	for(int v : g[r])
		if(dist[l][v] > dist[l][r])
			coloco = std::max(coloco, dfs(l, v));
	here += coloco;
	return here;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	for(int i = 1; i <= n; i++)
		get(i, 0, i), sz[i][i] = 0;
	memset(dp, 0xff, sizeof dp);
	unsigned int ans = 0;
	for(int i = 1; i <= n; i++)
		dfs(i, i), ans = std::max(ans, dp[i][i]);
	printf("%u\n", ans);
}