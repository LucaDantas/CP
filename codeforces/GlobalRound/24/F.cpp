#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2010;

long long f[maxn][maxn];

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return 1;
	}
} dsu;

struct Edge { int a, b; long long w; bool operator<(Edge o) { return w < o.w; } };

vector<Edge> a;

vector<int> g[maxn];

int dfs(int u, int p) {
	int sz = 1;
	for(int v : g[u]) if(v != p) {
		int aq = dfs(v, u);
		printf("%d %d %lld\n", u, v, (f[u][u] - f[u][v]) / aq);
		sz += aq;
	}
	return sz;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			scanf("%lld", &f[i][j]);
			a.push_back({i, j, f[i][j]});
			f[j][i] = f[i][j];
		}
	}
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end()); // ordena do maior peso pro menor
	for(auto [a, b, w] : a)
		if(dsu.join(a, b))
			g[a].push_back(b), g[b].push_back(a);
	dfs(1, 0);
}
