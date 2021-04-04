#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 4e5+10;

int f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i;
		for(int j = 2*i; j < maxn; j += i)
			f[j] = f[i];
	}
}

std::vector<int> div(int n) {
	std::vector<int> ans;
	while(n > 1) {
		ans.push_back(f[n]);
		n /= f[n];
	}
	return ans;
}

std::vector<int> g[maxn], dp[maxn];
int ans[maxn];
int sz[maxn];

void dfs(int u, int p = 0) {
	if(!g[u].size()) return (void)(sz[u] = 1);
	for(int& v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		if(dp[v].size() > dp[g[u][0]].size())
			std::swap(v, g[u][0]);
	}
	std::swap(dp[u], dp[g[u][0]]), sz[u] = sz[g[u][0]];
	for(int v : g[u]) {
		if(v == p || v == g[u][0]) continue;
		for(int x : dp[v])
			dp[u].push_back(x);
		dp[u].push_back(sz[u] + sz[v]);
		dp[u].push_back(-sz[u]);
		dp[u].push_back(-sz[v]);
		sz[u] += sz[v];
	}
	sz[u]++;
}

int main() {
	sieve();
	int n; scanf("%d", &n);
	for(int i = 2, p; i <= n; i++)
		scanf("%d", &p), g[p].push_back(i);
	dfs(1);
	std::sort(dp[1].begin(), dp[1].end(), [](int a, int b) { return std::abs(a) > std::abs(b); });
	for(int i = maxn-1, ativos = 0, ptr = 0; i >= 2; i--) {
		for(; ptr < dp[1].size() && std::abs(dp[1][ptr]) >= i; ptr++)
			ativos += dp[1][ptr]>0?1:-1;
		if(!ativos) continue;
		std::vector<int> d = div(i);
		for(int x : d)
			ans[x] += ativos;
	}
	int qtd = 0;
	for(int i = 0; i < maxn; i++)
		if(ans[i]) ++qtd;
	printf("%d\n", qtd);
	for(int i = 0; i < maxn; i++)
		if(ans[i]) printf("%d %d\n", i, ans[i]);
}