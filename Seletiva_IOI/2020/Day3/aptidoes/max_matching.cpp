#include<cstdio>
#include<vector>
#include<array>
#include<algorithm>
#include<cassert>
#include<cstring>

constexpr int maxn = 5e3+10;

int par[maxn], n;
bool mark[maxn];

std::array<int, 3> val[maxn];
std::vector<int> g[maxn];

bool dfs(int u) {
	// find augmenting paths
	mark[u] = 1;
	if(u > n) return par[u]?dfs(par[u]):1;
	for(int v : g[u]) {
		if(mark[v] || !dfs(v)) continue;
		par[u] = v, par[v] = u;
		return 1;
	}
	return 0;
}

int main() {
	int m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int x, y, k; scanf("%d %d %d", &x, &y, &k);
		val[i] = {x, y, i};
		for(int j = 0, x; j < k; j++)
			scanf("%d", &x), g[i].push_back(x + n);
	}
	int q; scanf("%d", &q); assert(q == 1);
	int A, B; scanf("%d %d", &A, &B);
	std::sort(val+1, val+n+1, [&](auto a, auto b) {
		return 1ll*a[0]*A + 1ll*a[1]*B > 1ll*b[0]*A + 1ll*b[1]*B;
	});
	long long ans = 0;
	for(int i = 1; i <= n; i++)
		if(dfs(val[i][2])) ans += 1ll*val[i][0]*A + 1ll*val[i][1]*B, memset(mark, 0, sizeof mark);
	printf("%lld\n", ans);
}