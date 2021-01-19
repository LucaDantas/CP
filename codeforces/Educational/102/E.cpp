#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using piii = pair<ll, pii>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 2e5+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll dist[maxn][4];

vector<pii> g[maxn];

bool mark[maxn][4];

void dijsktra() {
	for(int i = 0; i < maxn; i++)
		for(int mask = 0; mask < 4; mask++)
			dist[i][mask] = inf;
	
	priority_queue<piii, vector<piii>, greater<piii>> q;
	dist[1][0] = 0;
	q.push({0, {1, 0}});

	while(q.size()) {
		auto [u, mask] = q.top().ss; q.pop();
		if(mark[u][mask]) continue;
		mark[u][mask] = 1;

		for(pii pp : g[u]) {
			auto [v, w] = pp;
			
			if(dist[v][mask] > dist[u][mask] + w) {
				dist[v][mask] = dist[u][mask] + w;
				q.push({dist[v][mask], {v, mask}});
			}
			
			if(!(mask&1) && dist[v][mask|1] > dist[u][mask]) {
				dist[v][mask|1] = dist[u][mask];
				q.push({dist[v][mask|1], {v, mask|1}});
			}

			if(!(mask&2) && dist[v][mask|2] > dist[u][mask] + 2ll*w) {
				dist[v][mask|2] = dist[u][mask] + 2ll*w;
				q.push({dist[v][mask|2], {v, mask|2}});
			}

			if(!mask && dist[v][3] > dist[u][mask] + 1ll*w) {
				dist[v][3] = dist[u][mask] + 1ll*w;
				q.push({dist[v][3], {v, 3}});
			}
		}
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].pb({b, w});
		g[b].pb({a, w});
	}
	dijsktra();
	for(int i = 2; i <= n; i++)
		printf("%lld ", dist[i][3]);
	printf("\n");
}