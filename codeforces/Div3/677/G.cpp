#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e3+10;
constexpr int inf = 0x3f3f3f3f;

vector<pii> g[maxn];

struct Edge
{
	int a, b, w;
} edges[maxn];

int dist[maxn][maxn], ans[maxn];

bool mark[maxn];

void dijkstra(int s) {
	for(int i = 0; i < maxn; i++)
		dist[i][s] = inf;
	dist[s][s] = 0;
	memset(mark, 0, sizeof mark);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, s});
	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(pii pp : g[u]) {
			int v = pp.ff, w = pp.ss;
			if(dist[v][s] > dist[u][s] + w) {
				dist[v][s] = dist[u][s] + w;
				q.push({dist[v][s], v});
			}
		}
	}
}

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		edges[i] = {a, b, w};
		g[a].pb({b, w});
		g[b].pb({a, w});
	}
	for(int i = 1; i <= n; i++)
		dijkstra(i);
	while(k--) {
		int a, b; scanf("%d %d", &a, &b);
		for(int i = 0; i < m; i++) {
			if(dist[edges[i].a][a] > dist[edges[i].b][a])
				swap(edges[i].a, edges[i].b);
			ans[i] += min(dist[a][b], dist[edges[i].a][a]+dist[edges[i].b][b]);
		} 
	}
	printf("%d\n", *min_element(ans, ans+m));
}