#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int maxn = 1e5+10;

struct DP {
	int ini, fim; vector<int> ordem;
	DP(int _ini = 0, int _fim = 0, vector<int> sla = {}) : ini(_ini), fim(_fim), ordem(sla) {}
	bool operator<(const DP& o) const { return ini < o.ini; }
};

vector<int> g[maxn];
vector<DP> dp[maxn];

int sv[1<<8];
vector<int> ordem[1<<8];

void dfs(int u) {
	if(!g[u].size()) return; // sou um consultant
	
	for(int v : g[u])
		dfs(v); // calculo a dp de todos os meus filhos primeiro
	
	int k = g[u].size();

	for(int i = 0; i < (int)g[u].size(); i++) {
		int v = g[u][i];
		for(auto par : dp[v]) {
			int ini = par.ini, fim = par.fim;
			for(int i = 0; i < (1 << k); i++)
				sv[i] = 0x3f3f3f3f, ordem[i].clear();

			sv[1<<i] = fim; // coloco esse cara que é o meu caso base
			ordem[1<<i] = {g[u][i]};
			
			for(int mask = 1<<i; mask < (1 << k); mask++) if(sv[mask] < 0x3f3f3f3f) {
				for(int j = 0; j < k; j++) if(!(mask & (1 << j)))
					if(lower_bound(dp[g[u][j]].begin(), dp[g[u][j]].end(), DP(sv[mask],0)) != dp[g[u][j]].end()) {
						int novo = lower_bound(dp[g[u][j]].begin(), dp[g[u][j]].end(), DP(sv[mask],0))->fim;
						if(novo < sv[mask | (1 << j)]) {
							sv[mask | (1 << j)] = novo;
							ordem[mask].push_back(g[u][j]);
							ordem[mask | (1 << j)] = ordem[mask];
							ordem[mask].pop_back();
						}
					}
			}

			if(sv[(1<<k)-1] < 0x3f3f3f3f)
				dp[u].push_back({ini, sv[(1<<k)-1], ordem[(1<<k)-1]});
		}
	}

	sort(dp[u].begin(), dp[u].end());
	static vector<DP> pareto; pareto.clear();
	for(auto p : dp[u]) {
		while(pareto.size() && pareto.back().fim >= p.fim)
			pareto.pop_back();
		pareto.push_back(p);
	}
	dp[u] = pareto;
}

vector<int> ans[maxn];

void get(int u, int ini) {
	auto it = lower_bound(dp[u].begin(), dp[u].end(), DP(ini, 0));

	if(!g[u].size()) return (void)(ans[u] = {it->ini}); // se eu sou um consultant a minha resposta é o valor que eu escolhi

	ans[u] = it->ordem;
	int tempo = ini;
	for(int v : it->ordem) {
		get(v, tempo);
		tempo = lower_bound(dp[v].begin(), dp[v].end(), DP(tempo))->fim;
	}
}

int main() {
	int n; scanf("%d", &n);

	for(int i = 1; i <= n; i++) {
		int t; scanf("%d", &t); // type of the node
		if(t == 1) {
			// manager
			int k; scanf("%d", &k);
			g[i].resize(k);
			for(int& x : g[i])
				scanf("%d", &x);
		} else {
			// consultant
			int m; scanf("%d", &m);
			dp[i].resize(m);
			for(int j = 0; j < m; j++) {
				int val; scanf("%d", &val);
				dp[i][j] = {val, val};
			}
			sort(dp[i].begin(), dp[i].end());
		}
	}

	int recupera; scanf("%d", &recupera);

	dfs(1);

	puts(dp[1].size() ? "Yes" : "No");

	if(recupera && dp[1].size()) {
		get(1, dp[1].front().ini);

		for(int i = 1; i <= n; i++) {
			for(int x : ans[i])
				printf("%d ", x);
			puts("");
		}
	}
}
