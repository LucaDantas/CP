#include <cstdio>
#include <vector>

constexpr int maxn = 1e5+10;

std::vector<int> g[maxn];

int max(int x, int y) { return x > y ? x : y; }

int dfs(int u, int p = 0) {
	int here = 0, maior = 0;
	for(int v : g[u]) {
		if(v == p) continue;
		int aq = dfs(v, u);
		if(aq & here)
			maior = max(maior, 32 - __builtin_clz(aq & here));
		here |= aq;
	}
	here += 1 << maior;
	if(maior) here >>= maior, here <<= maior;
	return here;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int ans = dfs(1);
	printf("%d\n", 31 - __builtin_clz(ans));
}
