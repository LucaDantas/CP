#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 1e5+10;

int last[maxn], dp[maxn], mark[maxn];

std::vector<int> g[maxn], ord;

void dfs(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(!mark[v]) dfs(v);
	ord.push_back(u);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, k; i <= n; i++) {
		scanf("%d", &k);
		for(int j = 0, v; j < k; j++) {
			scanf("%d", &v);
			// Make 0 point to everyone
			g[last[v]].push_back(i);
			last[v] = i;
		}
	}
	dfs(0); ord.pop_back(); // remove 0
	std::reverse(ord.begin(), ord.end());
	int ans = 0;
	for(int i = 0; i < n; i++) {
		ans = std::max(ans, dp[ord[i]]);
		for(int v : g[ord[i]])
			dp[v] = std::max(dp[v], dp[ord[i]] + 1);
	}
	printf("%d\n", ans+1);
}