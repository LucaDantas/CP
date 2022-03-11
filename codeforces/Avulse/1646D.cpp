#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<int> g[maxn];

struct DP {
	int val, soma;
	void operator+=(const DP& o) { val += o.val; soma += o.soma; }
	bool operator>(const DP& o) const { return val != o.val ? val > o.val : soma < o.soma; }
	bool operator<(const DP& o) const { return !(*this > o); } // na realidade isso é >= mas tanto faz pq só uso no max
} dp[maxn][2];

// dp[1] -> sou dos caras bons, dp[0] -> não sou dos bons, logo meu valor é 1
void dfs(int u, int p = 0) {
	dp[u][1] = {1, (int)g[u].size()};
	dp[u][0] = {0, 1};
	for(int v : g[u]) if(v != p) {
		dfs(v, u);
		dp[u][1] += dp[v][0];
		dp[u][0] += max(dp[v][0], dp[v][1]);
	}
}

int ans[maxn];

void get(int u, int cor, int p = 0) {
	ans[u] = cor == 0 ? 1 : (int)g[u].size();
	for(int v : g[u]) if(v != p) {
		if(cor == 0) get(v, dp[v][1] > dp[v][0], u);
		else get(v, 0, u);
	}
}

int main() {
	int n; scanf("%d", &n);
	if(n == 2) return puts("2 2\n1 1"), 0;
	for(int i = 1; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].push_back(b), g[b].push_back(a);
	}
	dfs(1);
	DP best = max(dp[1][0], dp[1][1]);
	get(1, dp[1][1] > dp[1][0]);
	printf("%d %d\n", best.val, best.soma);
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	puts("");
}
