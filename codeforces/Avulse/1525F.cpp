#include <cstdio>
#include <vector>
#include <cstring>

constexpr int maxn = 105;

std::vector<int> g[maxn];

int par[maxn], n, matching_size;

bool mark[maxn];

bool dfs(int u) {
	mark[u] = 1;
	if(u > n)
		return par[u] ? dfs(par[u]) : 1;
	for(int v : g[u]) if(!mark[v] && dfs(v)) {
		par[u] = v, par[v] = u;
		return 1;
	}
	return 0;
}

int fast_kuhn() {
	bool aux = 1;
	int ans = 0;
	while(aux) {
		aux = 0;
		for(int i = 1; i <= n; i++)
			if(!par[i] && !mark[i] && dfs(i)) aux = 1, ++ans;
		memset(mark, 0, sizeof mark);
	}
	return ans;
}

void dfs2(int u) {
	mark[u] = 1;
	if(u > n) return dfs2(par[u]);
	for(int v : g[u]) if(!mark[v])
		dfs2(v);
}

std::vector<int> vertex_cover() {
	matching_size = fast_kuhn();

	memset(mark, 0, sizeof mark);
	for(int i = 1; i <= n; i++)
		if(!par[i]) dfs2(i);
	
	std::vector<int> ans;
	for(int i = 1; i <= (n<<1); i++)
		if((mark[i]^(i<=n))) ans.push_back(i);

	return ans;
}

int main() {
	int m, k; scanf("%d %d %d", &n, &m, &k);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b+n), g[b+n].push_back(a);

	std::vector<int> vt = vertex_cover();
	int safe = n-matching_size - 1;

	std::vector<int> qtd(k);
	for(int i = 0; i < k; i++)
		qtd[i] = (i >= safe) + (i > 0 ? qtd[i-1] : 0);

	std::vector<int> x(k), y(k);
	for(int i = 0; i < k; i++)
		scanf("%d %d", &x[i], &y[i]);

	std::vector<std::vector<long long>> dp(k+1, std::vector<long long>(k+1, -0x3f3f3f3f3f3f3f3f));
	std::vector<std::vector<int>> pai(k+1, std::vector<int>(k+1));

	dp[0][0] = 0;
	for(int i = 0; i < k; i++)
		for(int tem = 0; tem <= k; tem++)
			for(int coloca = 0; coloca + tem <= k; coloca++) if(tem + coloca >= qtd[i])
				if(dp[i+1][tem+coloca] < dp[i][tem] + std::max(0ll, x[i] - 1ll * coloca * y[i]))
					dp[i+1][tem+coloca] = dp[i][tem] + std::max(0ll, x[i] - 1ll * coloca * y[i]), pai[i+1][tem+coloca] = tem;

	auto ajeita = [](int X) { if(X <= n) return X; return -(X-n); };

	std::vector<int> ans;
	for(int i = k, lvl = qtd[k-1]; i > 0; i--) {
		ans.push_back(0);
		int aq = lvl;
		while(lvl > pai[i][aq])
			--lvl, ans.push_back(ajeita(vt.back())), vt.pop_back();
	}

	printf("%ld\n", ans.size());
	for(int i = (int)ans.size() - 1; i >= 0; i--)
		printf("%d ", ans[i]);
	puts("");
}
