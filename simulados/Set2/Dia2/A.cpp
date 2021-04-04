#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int cor[maxn], sz;
vector<int> g[maxn];

void dfs(int u) {
	++sz;
	for(int v : g[u])
		if(!cor[v]) cor[v] = 3 - cor[u], dfs(v);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	bool ok = 1;
	for(int i = 1; i <= n; i++)
		if(!cor[i]) sz = 0, cor[i] = 1, dfs(i), ok &= sz > 1;
	if(!ok) return puts("NIE"), 0;
	puts("TAK");
	for(int i = 1; i <= n; i++)
		puts(cor[i]==1?"K":"S");
}