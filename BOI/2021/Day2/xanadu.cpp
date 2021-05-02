#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

vector<int> g[maxn];

int dp[maxn][2][2], new_dp[maxn][2][2], state[maxn];

void min_self(int& a, int b) { a = min(a, b); }

void dfs(int u, int p = 0) {
	dp[u][0][state[u]] = 0;
	dp[u][0][!state[u]] = inf;

	dp[u][1][state[u]] = inf;
	dp[u][1][!state[u]] = 1;

	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);

		for(int i : {0, 1}) { // vou me ativar ou n
			for(int j : {0, 1}) { // estou ligado ou desligado - ja contando a minha ativação
				for(int k : {0, 1}) { // ativo-inativo de v
					for(int l : {0, 1}) { // ligado-desligado de u
						if(i ^ l) continue; // n posso juntar pq eu preciso garantir q tá todo mundo desligado
						min_self(new_dp[u][i][j^k], dp[u][i][j] + dp[v][k][l]);
					}
				}
			}
		}

		for(int i : {0, 1}) for(int j : {0, 1})
			dp[u][i][j] = new_dp[u][i][j], new_dp[u][i][j] = inf;
	}
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	for(int i = 1; i <= n; i++)
		scanf("%d", state + i);
	for(int u = 0; u < maxn; u++)
		for(int i : {0, 1}) for(int j : {0, 1})
			new_dp[u][i][j] = inf;
	dfs(1);
	int ans = min(dp[1][0][0], dp[1][1][0]);
	if(ans == inf) puts("impossible");
	else printf("%d\n", ans);
}