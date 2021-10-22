#include <cstdio>
#include <vector>

constexpr int maxn = 3e5+10;

inline void swap(int& a, int& b) { int aux = a; a = b; b = aux; }

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b]) swap(a, b);
		peso[a] += peso[b];
		pai[b] = a;
		return 1;
	}
} dsu;

std::vector<int> g[maxn];

int p[maxn], depth[maxn], mark[maxn], ans; // mark é pra saber se a aresta dele pro pai tá marcada

void dfs(int u) {
	for(int v : g[u]) if(v != p[u]) {
		p[v] = u;
		depth[v] = depth[u]+1;
		dfs(v);
	}
}

bool get(int u) {
	int qtd = 0;
	for(int v : g[u])
		if(v != p[u]) qtd += get(v);
	ans += qtd >> 1;
	if((qtd&1) && !mark[u]) ++ans;
	return mark[u];
}

struct Qr { int a, b, lca; } qrs[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		if(dsu.join(a, b)) g[a].push_back(b), g[b].push_back(a);
	}

	dfs(1);

	int q; scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		int a, b; scanf("%d %d", &a, &b);
		qrs[i] = {a, b, -1};
		for(; a != b; mark[a] ^= 1, a = p[a])
			if(depth[a] < depth[b]) swap(a, b);
		qrs[i].lca = a;
	}

	bool ok = 1;
	for(int i = 1; i <= n; i++)
		ok &= !mark[i];

	if(ok) {
		puts("YES");

		for(int i = 0; i < q; i++) {
			auto [a, b, lca] = qrs[i];
			printf("%d\n", depth[a] + depth[b] - (depth[lca] << 1) + 1);
			while(a != lca) printf("%d ", a), a = p[a];
			printf("%d", lca);
			std::vector<int> aux;
			while(b != lca) aux.push_back(b), b = p[b];
			for(int t = ((int)aux.size()) - 1; t >= 0; t--)
				printf(" %d", aux[t]);
			puts("");
		}

		return 0;
	}

	get(1);
	printf("NO\n%d\n", ans);
}
