#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) (a).begin(),(a).end()

constexpr int maxn = 510;

vector<int> g[maxn];

int a[maxn], dp[maxn];

vector<int> ord;

bool mark[maxn];

void dfs(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(!mark[v])
			dfs(v);
	ord.pb(u);
}

int main() {
	int n, m, p; scanf("%d %d %d", &n, &m, &p);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d %d", &x, &y);
		if(a[y] > a[x])
			swap(x, y);
		if(a[x] != a[y])
			g[x].pb(y);
	}
	// O grafo já foi construído somente com os edges válidos
	// agr só precisa fazer a top sort e pegar o mais longe
	// o grafo é garantido de não ter ciclos por causa das alturas
	dfs(p);
	reverse(all(ord));
	int ans = 0;
	for(int u : ord) {
		ans = max(ans, dp[u]);
		for(int v : g[u])
			dp[v] = max(dp[v], dp[u]+1);
	}
	printf("%d\n", ans);
}
