#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define pb push_back
#define ff first
#define ss second

constexpr int maxn = 2e5+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
	int v;
	ll t, i, f;
};

vector<Edge> g[maxn];

ll dist[maxn];

bool mark[maxn];

void dijkstra(int s, ll l) {
	for(int i = 0; i < maxn; i++)
		dist[i] = -inf;
	dist[s] = l;

	priority_queue<pii> q;
	q.push({l, s});

	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(auto pp : g[u]) {
			if(mark[pp.v]) continue;
			if(dist[u] - pp.t < pp.i) continue;
			ll w = dist[u] - pp.t - (((dist[u] - pp.t - pp.i)%pp.f+pp.f)%pp.f);
			if(w < 0) continue;
			if(dist[pp.v] < w) {
				dist[pp.v] = w;
				q.push({w, pp.v});
			}
		}
	}
}

int main() {
	int n, m; ll l; scanf("%d %d %lld", &n, &m, &l);
	while(m--) {
		int a, b; ll t, i, f;
		scanf("%d %d %lld %lld %lld", &a, &b, &t, &i, &f);
		g[b].pb({a, t, i, f}); // a gente inverte o grafo e comeca do fim
	}
	dijkstra(n-1, l);
	printf("%lld\n", dist[0]<0?-1:dist[0]);
}