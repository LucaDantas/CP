#include <cstdio>
#include <vector>

constexpr int maxn = 2e5+10;

std::vector<int> g[maxn];

int dist[maxn], color[maxn], t = 1, l, r;
bool has[maxn];

void dfs(int u, int p = 0) {
	for(int v : g[u]) {
		if(v == p) continue;
		dist[v] = dist[u] + 1;
		dfs(v, u);
	}
}

void pre(int u, int p = 0) {
	has[u] = u == r;
	for(int& v : g[u]) {
		if(v != p) {
			pre(v, u);
			has[u] |= has[v];
			if(has[v]) std::swap(v, g[u][0]);
		}
	}
	if(g[u].size() && has[u]) std::swap(g[u][0], g[u].back());
}

void get(int u, int p = 0) {
	color[u] = t++;
	for(int v : g[u])
		if(v != p) get(v, u), t++;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	dfs(1);
	l = 1, r = 1;
	for(int i = 1; i <= n; i++)
		if(dist[i] > dist[l]) l = i;
	dist[l] = 0;
	dfs(l);
	for(int i = 1; i <= n; i++)
		if(dist[i] > dist[r]) r = i;
	pre(l);
	get(l);
	for(int i = 1; i <= n; i++)
		printf("%d%c", color[i], " \n"[i==n]);
}