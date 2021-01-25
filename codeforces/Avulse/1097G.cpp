/*
I've used a slightly different approach from the editorial because
instead of counting in how many subgraphs that subset of edges is
chosen I counted in how many ways I can choose l different edges
in some given subgraph, and how many times that subgraph can appear

To optimize it to O(nk) instead of O(nk²) I used the same trick
they've suggested: instead of looping to k every time, I loop
up to min(k, size-1). But to do so I had to count only different
and sorted subsets of edges and then update it with some math
magic at the end because they don't necessarely need to follow
those specifications in the final answer
*/

#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())

constexpr int maxn = 1e5+10, maxk = 210, mod = 1000000007;

int dp[maxn][maxk][2], fat[maxn], inv_fat[maxn], tam[maxn], qtd[maxn], k;

vector<int> g[maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = 1ll*ans*b%mod;
		b = 1ll*b*b%mod;
		e >>= 1;
	}
	return ans;
}

void calc() {
	fat[0] = 1;
	inv_fat[0] = 1;
	for(int i = 1; i < maxk; i++)
		fat[i] = 1ll*fat[i-1]*i%mod, inv_fat[i] = power(fat[i], mod-2)%mod;
}

int choose(int a, int b) {
	return (1ll*fat[a]*inv_fat[a-b]%mod)*inv_fat[b]%mod;
}

void dfs(int u, int p) {
	tam[u] = 1;

	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);

		for(int i = min(tam[u]-1, k); i >= 0; i--) {
			for(int j = min({tam[v]-1, k-i}); j >= 0; j--) {
				int soma = (int)((1ll*dp[v][j][0] + dp[v][j][1]*2ll + (j==0))%mod);
				if(i+j < k)
					dp[u][i+j+1][1] += (i==0) * soma,
					dp[u][i+j+1][0] += (2ll*dp[u][i][1] + dp[u][i][0]) * soma % mod;
				dp[u][i+j][0] += (2ll*dp[u][i][1] + dp[u][i][0]) * soma % mod;
				dp[u][i+j][1] += (i==0) * soma;

				dp[u][i+j][0] %= mod;
				dp[u][i+j][1] %= mod;
				dp[u][i+j+1][0] %= mod;
				dp[u][i+j+1][1] %= mod;
			}
		}
		tam[u] += tam[v];
	}
}

int main() {
	calc();
	int n; scanf("%d %d", &n, &k);
	for(int i = 1; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}

	dfs(1, 0);

	for(int i = 0; i <= k; i++)
		for(int j = i; j >= 1; j--)
			qtd[i] += 1ll*power(j, k)*choose(i, j)*((i-j)%2==0?1:-1)%mod, qtd[i] %= mod;

	int ans = 0;
	for(int u = 1; u <= n; u++)
		for(int i = 1; i <= k; i++)
			ans += 1ll*(dp[u][i][0]+dp[u][i][1])*qtd[i]%mod, ans %= mod;

	printf("%d\n", (ans+mod)%mod);
}