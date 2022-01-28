#include <cstdio>
#include <vector>
#include <cmath>

const int maxn = 1e4+10;

std::vector<int> g[maxn];
int qtd[maxn], mark[maxn];

void dfs(int u) {
	mark[u] = 1;
	for(int i = 0; i < (int)g[u].size(); i++) {
		int v = g[u][i];
		if(mark[v]) continue;
		dfs(v), qtd[u] += qtd[v];
	}
}

int sum(int n) { int ans = 0; for(int i = 1; i <= n; i++) ans += abs(qtd[i]); return ans; }

int main() {
	int n; scanf("%d", &n);
	do {
		for(int i = 1; i <= n; i++) qtd[i] = 0, g[i].clear(), mark[i] = 0;

		for(int i = 1; i <= n; i++) {
			int u; scanf("%d", &u);
			scanf("%d", &qtd[u]); qtd[u]--;
			int qc; scanf("%d", &qc);
			while(qc--) {
				int v; scanf("%d", &v);
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}

		dfs(1);

		printf("%d\n", sum(n));

		scanf("%d", &n);
	} while(n != 0);
}
