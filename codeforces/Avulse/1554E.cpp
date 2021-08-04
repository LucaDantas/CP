#include <cstdio>
#include <vector>

constexpr int maxn = 1e5+10, mod = 998244353;

int min(int a, int b) { return a < b ? a : b; }

std::vector<int> g[maxn];
int pot[maxn], dp[maxn], ok = 1;

void dfs(int u, int p, int opa) {
	if(!ok) return;
	for(int v : g[u])
		if(v != p) dfs(v, u, opa);
	if(dp[u] % opa != 0) {
		if(p) ++dp[u];
		if(dp[u] % opa != 0) ok = 0;
	} else if(p) ++dp[p];
}

int main() {
	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = (pot[i-1]<<1) % mod;
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0; i <= n; i++)
			g[i].clear(), dp[i] = 0;

		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

		std::vector<int> ans(n+1);
		int foi = 0;
		for(int i = 2; i <= n; i++) {
			if((n-1)%i) continue;
			ok = 1, dfs(1, 0, i);
			ans[i] = ok, foi += ok;
			for(int j = 1; j <= n; j++)
				dp[j] = 0;
		}

		ans[1] = pot[n-1];
		for (int i = n; i >= 1; i--)
			for (int j = i + i; j <= n; j += i)
				ans[i] = (ans[i] - ans[j] + mod) % mod;

		for(int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		puts("");
	}
}
