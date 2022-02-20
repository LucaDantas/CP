#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10, maxk = 5;

int color[maxn], k;

long long dp[1<<maxk][maxn];

bool vis[1<<maxk][maxn];

vector<int> g[maxn];

long long solve(int x, int mask) {
	if(vis[mask][x]) return dp[mask][x];

	vis[mask][x] = 1;
	dp[mask][x] = 1;

	for(int v : g[x])
		if(!(mask & color[v])) dp[mask][x] += solve(v, mask ^ color[v]);

	return dp[mask][x];
}

int main() {
	int n, m; scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &color[i]), color[i] = 1 << (color[i]-1);

	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

	long long ans = 0;

	for(int i = 1; i <= n; i++)
		ans += solve(i, color[i]) - 1;

	printf("%lld\n", ans);
}
