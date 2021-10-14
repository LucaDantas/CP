#include <cstdio>
#include <vector>

constexpr int maxn = 1e3+10;

std::vector<int> g[maxn];

int a[maxn], back[maxn], p[maxn], t;

void dfs(int u) {
	a[u] = ++t; back[t] = u;
	for(int v : g[u])
		if(v != p[u]) p[v] = u, dfs(v);
}

int query(int m) {
	printf("? %d", m);
	for(int i = 1; i <= m; i++)
		printf(" %d", back[i]);
	puts("");
	fflush(stdout);
	int v; scanf("%d", &v);
	return v;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++)
		scanf("%d %d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	dfs(1);
	int l = 2, r = t, mx = query(t), ans = -1;
	for(int i = 1; i < 12 && l <= r; i++) {
		int m = (l+r) >> 1;
		if(query(m) == mx) r = m-1, ans = m;
		else l = m+1;
	}
	printf("! %d %d\n", p[back[ans]], back[ans]);
}
