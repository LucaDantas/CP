#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10;

vector<int> g[maxn], ord;
vector<pii> dag[maxn];

struct Edge
{
	int a, b, z;
} edges[maxn];

int k, dist[maxn][2], dp[maxn], pai[maxn];
bool mark[maxn];

void dfs(int u) {
	mark[u] = 1;
	for(auto pp : dag[u]) {
		int v = pp.ff;
		if(!mark[v])
			dfs(v);
	}
	ord.pb(u);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, z; scanf("%d %d %d", &a, &b, &z);
		edges[i] = {a, b, z};
		g[a].pb(b);
		g[b].pb(a);
	}

	for(int s : {1, n}) {
		queue<int> q;
		q.push(s);

		memset(mark, 0, sizeof mark);
		mark[s] = 1;

		while(q.size()) {
			int u = q.front(); q.pop();
			for(auto v : g[u])
				if(!mark[v])
					dist[v][k] = dist[u][k]+1, q.push(v), mark[v] = 1;
		}
		k++;
	}

	for(int i = 0; i < m; i++) {
		if(dist[edges[i].a][0] > dist[edges[i].b][0])
			swap(edges[i].a, edges[i].b);
		if(dist[edges[i].a][0] + dist[edges[i].b][1] + 1 == dist[n][0])
			dag[edges[i].a].pb({edges[i].b, edges[i].z?-1:1});
	}

	memset(mark, 0, sizeof mark);
	dfs(1);
	reverse(ord.begin(), ord.end());

	for(int i = 0; i < maxn; i++)
		dp[i] = maxn;
	dp[1] = 0;

	int ans = 0;
	for(int i = 0; i < m; i++)
		ans += edges[i].z;

	for(auto u : ord)
		for(auto v : dag[u])
			if(dp[u] + v.ss < dp[v.ff])
				pai[v.ff] = u, dp[v.ff] = dp[u] + v.ss;


	set<pii> st;

	int now = n;
	while(now != 1) {
		st.insert({pai[now], now});
		now = pai[now];
	}

	printf("%d\n", ans + dp[n]);
	for(int i = 0; i < m; i++) {
		if(st.count({edges[i].a, edges[i].b}) && !edges[i].z)
			printf("%d %d %d\n", edges[i].a, edges[i].b, 1);
		else if(!st.count({edges[i].a, edges[i].b}) && edges[i].z)
			printf("%d %d %d\n", edges[i].a, edges[i].b, 0);
	}
}