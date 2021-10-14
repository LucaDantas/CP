#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 55, maxc = 110;

vector<int> g[maxn];
int mark[maxn];

int a[3], dist[maxn];
bool foi[maxn][maxc][3];

void dfs(int u, int d, int cor) {
	if(foi[u][d][cor]) return;
	foi[u][d][cor] = 1;
	if(!d) return (void)(mark[u] |= (1<<cor));
	for(int v : g[u])
		dfs(v, d-1, cor);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	scanf("%d %d %d", &a[0], &a[1], &a[2]);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d %d", &x, &y);
		g[y].push_back(x);
	}

	memset(dist, 0x3f, sizeof dist);

	queue<int> q;
	q.push(n);
	dist[n] = 0;

	while(q.size()) {
		int u = q.front(); q.pop();
		for(int j = 0; j < 3; j++) dfs(u, a[j], j);
		for(int i = 1; i < n; i++)
			if(mark[i] == 7 && dist[i] == 0x3f3f3f3f)
				dist[i] = dist[u]+1, q.push(i);
	}

	if(dist[1] < 0x3f3f3f3f)
		printf("%d\n", dist[1]);
	else puts("IMPOSSIBLE");
}
