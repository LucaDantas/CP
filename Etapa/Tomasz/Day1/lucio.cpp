#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int U[17];

int dp[maxn];

int pai[maxn], nivel[maxn];

int anc[2][maxn];

bool vis[maxn];

map<pii, int> mark;

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u, nivel[v] = nivel[u]+1;
		dfs(v, u);
	}
}

void solve(int u, int p)
{
	dp[u] = 0, vis[u] = 1;
	vector<int> all;

	for (auto v: grafo[u])
	{
		if (v == p || mark[{u, v}] || mark[{v, u}]) continue;

		solve(v, u);

		all.push_back(dp[v]);
	}

	sort(all.begin(), all.end());

	int add = 1;

	for (int i = (int)(all.size())-1; i >= 0; i--)
	{
		dp[u] = max(dp[u], add + all[i]);
		++add;
	}
}

int doit(int v1, int v2, int v3)
{
	nivel[U[v1]] = 0, pai[U[v1]] = 0;

	dfs(U[v1], 0);

	if (nivel[U[v3]] < nivel[U[v2]]) swap(U[v2], U[v3]);

	int at = U[v2], ind0 = 0;
	while (at)
	{
		anc[0][ind0++] = at;
		at = pai[at];
	}

	at = U[v3];
	int ind1 = 0;
	while (at)
	{
		anc[1][ind1++] = at;
		at = pai[at];
	}

	int aux0 = 0, aux1 = 0;

	while (anc[0][aux0] != anc[1][aux1])
	{
		if (nivel[anc[0][aux0]] > nivel[anc[1][aux1]]) ++aux0;
		else ++aux1;
	}

	int ans = maxn;

	for (int i = 0; i < ind0; i++)
	{
		int ini = 0, fim = aux1-1, best = aux1;

		mark[{anc[0][i], pai[anc[0][i]]}] = 1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			mark[{anc[1][mid], pai[anc[1][mid]]}] = 1;

			solve(U[v2], 0); solve(U[v3], 0);

			if (dp[U[v3]] >= dp[U[v2]]) best = mid, fim = mid-1;
			else ini = mid+1;

			mark[{anc[1][mid], pai[anc[1][mid]]}] = 0;
		}

		int aux = maxn;

		if (best != aux1)
		{
			mark[{anc[1][best], pai[anc[1][best]]}] = 1;

			solve(U[v1], 0); solve(U[v3], 0);

			aux = max(dp[U[v1]], dp[U[v3]]);

			mark[{anc[1][best], pai[anc[1][best]]}] = 0;
		}

		--best;

		if(best >= 0)
			mark[{anc[1][best], pai[anc[1][best]]}] = 1;

		solve(U[v1], 0); solve(U[v2], 0);

		if(best >= 0)
			mark[{anc[1][best], pai[anc[1][best]]}] = 0;

		aux = min(aux, max(dp[U[v1]], dp[U[v2]]));

		ans = min(ans, aux);

		mark[{anc[0][i], pai[anc[0][i]]}] = 0;
	}

	return ans;
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	
	for (int i = 1; i <= k; i++)
		scanf("%d", &U[i]);

	vector<pii> edge;

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);

		edge.push_back({u, v});
	}

	if (k == 1)
	{
		solve(U[1], 0);
		printf("%d\n", dp[U[1]]);
		return 0;
	}

	if (k == 2)
	{
		dfs(U[1], 0);

		int at = U[2], ind = 0;
		while (at)
		{
			anc[0][ind++] = at;
			at = pai[at];
		}

		int ini = 0, fim = ind-1, best = ind;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			mark[{anc[0][mid], pai[anc[0][mid]]}] = 1;

			solve(U[1], 0); solve(U[2], 0);

			if (dp[U[2]] >= dp[U[1]]) best = mid, fim = mid-1;
			else ini = mid+1;

			mark[{anc[0][mid], pai[anc[0][mid]]}] = 0;
		}

		int ans = maxn;

		if (best != ind)
		{
			mark[{anc[0][best], pai[anc[0][best]]}] = 1;

			solve(U[2], 0);

			ans = dp[U[2]];

			mark[{anc[0][best], pai[anc[0][best]]}] = 0;
		}

		--best;

		mark[{anc[0][best], pai[anc[0][best]]}] = 1;

		solve(U[1], 0);

		ans = min(ans, dp[U[1]]);

		printf("%d\n", ans);

		return 0;
	}

	if (k == 3)
	{
		if (n > 1000) return 0;

		printf("%d\n", min({doit(1, 2, 3), doit(2, 1, 3), doit(3, 1, 2)}));
		return 0;
	}

	if (n <= 16)
	{
		int ans = maxn;

		for (int mask = 0; mask < (1<<edge.size()); mask++)
		{
			for (int i = 1; i <= n; i++)
				vis[i] = 0;

			for (int i = 0; i < (int)edge.size(); i++)
				mark[edge[i]] = 0;

			for (int i = 0; i < (int)edge.size(); i++)
				if (mask&(1<<i))
					mark[edge[i]] = 1;

			int aux = 0;

			for (int i = 1; i <= k; i++)
			{
				solve(U[i], 0);
				aux = max(aux, dp[U[i]]);
			}

			bool ok = 1;
			for (int i = 1; i <= n; i++)
				if (!vis[i])
					ok = 0;

			if (ok) ans = min(ans, aux);
		}

		printf("%d\n", ans);
		return 0;
	}
}
