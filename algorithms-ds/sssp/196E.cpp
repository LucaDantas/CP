#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pli = pair<ll,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b)
			return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return 1;
	}
} dsu;

struct Edge
{
	int a, b, w;
} edges[maxn];

vector<pii> g[maxn];
vector<int> p;

int portal[maxn];

ll dist[maxn];

bool mark[maxn];

void dijkstra() {
	for(int i = 1; i < maxn; i++)
		dist[i] = inf;
	priority_queue<pli, vector<pli>, greater<pli>> q;

	for(int x : p) {
		dist[x] = 0;
		portal[x] = x;
		q.push({0, x});
	}

	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(pii pp : g[u]) {
			int v = pp.ff, w = pp.ss;
			if(dist[v] > dist[u] + 1ll*w) {
				dist[v] = dist[u] + 1ll*w;
				portal[v] = portal[u];
				q.push({dist[v], v});
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].pb({b, w});
		g[b].pb({a, w});
		edges[i] = {a, b, w};
	}
	int k; scanf("%d", &k);
	p.resize(k);
	for(int i = 0; i < k; i++)
		scanf("%d", &p[i]);
	dijkstra();

	sort(edges, edges+m, [](Edge x, Edge y){
		return dist[x.a] + x.w + dist[x.b] < dist[y.a] + y.w + dist[y.b]; 
	});

	ll ans = dist[1];

	for(int i = 0; i < m; i++)
		if(dsu.join(portal[edges[i].a], portal[edges[i].b]))
			ans += dist[edges[i].a] + edges[i].w + dist[edges[i].b];

	printf("%lld\n", ans);
}