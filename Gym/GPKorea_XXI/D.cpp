#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 3e5+10;

int n, m;
vector<pii> grafo[maxn];

bool in[maxn];

struct Edge
{
	int u, v, w;
} edge[maxn];

struct BinaryLifting
{
	bool mark[maxn];
	int nivel[maxn], tab[maxn][20], mn[maxn][20];

	void dfs(int u, int p)
	{
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u, mn[v][0] = w;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j < 20; j++)
		{
			for (int i = 1; i <= n; i++)
			{
				tab[i][j] = tab[tab[i][j-1]][j-1];
				mn[i][j] = min(mn[i][j-1], mn[tab[i][j-1]][j-1]);
			}
		}
	}

	int get(int u, int v)
	{
		if (nivel[u] < nivel[v]) swap(u, v);

		int ans = 1e7+10;

		for (int i = 19; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v])
				ans = min(ans, mn[u][i]), u = tab[u][i];

		if (u == v) return ans;

		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
				ans = min({ans, mn[u][i], mn[v][i]}), u = tab[u][i], v = tab[v][i];

		return min({ans, mn[u][0], mn[v][0]});
	}
} LCA;

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(void)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
	}
} dsu;

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w};
	}

	sort(edge+1, edge+m+1, [&] (Edge a, Edge b) {return a.w > b.w;});

	ll ans = 0, tot = 1ll*n*(n-1)/2;
	dsu.init();

	for (int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;

		if (dsu.Find(edge[i].u) != dsu.Find(edge[i].v))
		{
			ll k = 1ll*dsu.peso[dsu.Find(u)]*dsu.peso[dsu.Find(v)];
			tot -= k;

			ans += 1ll*w*k;

			dsu.Join(u, v);
			grafo[u].push_back({v, w}); grafo[v].push_back({u, w});

			in[i] = 1;
		}
	}

	ans += tot;

	for (int i = 1; i <= n; i++)
		if (!LCA.mark[i])
			LCA.dfs(i, 0);

	LCA.build();

	bool ok = 1;

	for (int i = 1; i <= m; i++)
	{
		if (!in[i])
		{
			int u = edge[i].u, v = edge[i].v, w = edge[i].w;

			if (w < LCA.get(u, v))
				ok = 0;
		}
	}

	if (!ok) printf("-1\n");
	else printf("%lld\n", ans);
}
