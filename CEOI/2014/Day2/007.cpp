#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<int> g[maxn];

int dist[2][maxn];

void bfs(int k, int s) {
	dist[k][s] = 0;
	queue<int> q;
	q.push(s);

	while(q.size()) {
		int u = q.front(); q.pop();

		for(int v : g[u])
			if(dist[k][v] > dist[k][u]+1)
				dist[k][v] = dist[k][u]+1, q.push(v);
	}
}

bool mark[maxn];

void dfs(int u, int& mn) {
	mark[u] = 1;
	mn = min(mn, dist[0][u]);
	for(int v : g[u])
		if(!mark[v] && dist[0][v] == dist[1][v] && dist[0][v] == dist[0][u]-1) dfs(v, mn);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	int s, t, a, b; scanf("%d %d %d %d", &s, &t, &a, &b);

	for(int i = 0; i < m; i++) {
		int u, v; scanf("%d %d", &u, &v);
		g[u].push_back(v); g[v].push_back(u);
	}
	
	memset(dist, 0x3f, sizeof dist); // já coloco infinito pra todo mundo
	bfs(0, a);
	bfs(1, b);

	int especial = 0;
	if(dist[0][s] == dist[1][s] && dist[0][t] == dist[1][t]) {
		memset(mark, 0, sizeof mark);
		int S = 0x3f3f3f3f; dfs(s, S);

		memset(mark, 0, sizeof mark);
		int T = 0x3f3f3f3f; dfs(t, T);

		if(S > T) especial = 1;
	}

	printf("%d\n", max(-1, min(dist[0][t] - dist[0][s], dist[1][t] - dist[1][s]) - especial));
}
