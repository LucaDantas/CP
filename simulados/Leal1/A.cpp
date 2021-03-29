#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 310;

vector<int> g[maxn];

bool tem[maxn];

int dfs(int u, int p = 0) {
	int ans = -1 + tem[u];
	for(int v : g[u]) {
		if(v == p) continue;
		int a = dfs(v, u);
		if(a != -1) ans += (ans==-1) + 2 + a;
	}
	return ans;
}

int main() {
	int n, m, t = 0; scanf("%d %d", &n, &m);
	while(n + m) {
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
		for(int i = 0, a; i < m; i++)
			scanf("%d", &a), tem[a] = 1;
		printf("Teste %d\n%d\n", ++t, dfs(1));
		for(int i = 1; i <= n; i++)
			g[i].clear(), tem[i] = 0;
		scanf("%d %d", &n, &m);
	}
}