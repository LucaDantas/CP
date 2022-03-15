#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

vector<int> g[maxn];

int deep[maxn], prof[maxn];

void pre(int u, int p = 0) {
	for(int v : g[u]) if(v != p) {
		prof[v] = prof[u]+1;
		pre(v, u);
		deep[u] = max(deep[u], deep[v]+1);
	}
}

void clear() { memset(deep, 0, sizeof deep); memset(prof, 0, sizeof prof); }

int ans = 0;
int L, R;

void dfs(int u, int p, int tam_min) {
	if(g[u].size() == 1) {
		ans += prof[u] * R >= tam_min;
		return;
	}

	swap(*g[u].begin(), *find(g[u].begin(), g[u].end(), p)); // o pai tá sempre no inicio, então posso desconsiderar
	assert(g[u].front() == p);

	int sz = (int)(g[u].size());
	vector<int> pref(sz+1), suf(sz+1);
	
	for(int i = 1; i < sz; i++) {
		pref[i] = max(pref[i-1], deep[g[u][i]]+1);
		suf[i] = max(suf[i+1], deep[g[u][i]]+1);
	}

	for(int i = 1; i < sz; i++) {
		if(prof[u] * R < max(pref[i-1], suf[i+1]) * L) continue; // não da pra chegar nesse cara porque a aresta não vai pro inicio da dfs
		dfs(g[u][i], u, max(tam_min, prof[u] * R + max(pref[i-1], suf[i+1]) * L));
	}

	// o que eu preciso garantir:
	// dist(u, folha_final) * R >= max(pref[i-1], suf[i+1]) * L ==> prof[folha_final] * R >= prof[u] * R + max(pref[i-1], suf[i+1]) * L
	// (dist(u, folha_inicial) == prof[u]) * R >= max(pref[i-1], suf[i+1]) * L
	
	// quando eu chego na folha pra verificar a resposta:
	// prof[folha] * R >= tam_min ==> caminho válido
}

int diam_ini = 0;

int main() {
	int n; scanf("%d %d %d", &n, &L, &R);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

	pre(1, 0);
	int longe = max_element(prof+1, prof+1+n) - prof;
	clear();
	pre(longe, 0);
	diam_ini = *max_element(prof+1, prof+1+n);
	clear();
	
	for(int i = 1; i <= n; i++) if(g[i].size() == 1) {
		clear();
		pre(i, 0);
		// também preciso garantir que, além de todos os caminhos que se intersectam com o meu, o caminho é >= a todos os caminhos que nao intersectam
		dfs(g[i][0], i, diam_ini*L);
	}

	printf("%d\n", ans>>1);
}
