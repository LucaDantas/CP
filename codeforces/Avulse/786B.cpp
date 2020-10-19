#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pli = pair<ll,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e6+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

int n, max_node = 0;

vector<pii> g[maxn];

struct SegDesce
{
	void build(int node, int i, int j) {
		if(i == j)
			g[node+n].pb({i, 0}), max_node = max(max_node, node+n);
		else {
			int m = (i+j) >> 1;
			build(2*node, i, m); build(2*node+1, m+1, j);
			g[node+n].pb({2*node+n, 0});
			g[node+n].pb({2*node+1+n, 0});
		}
	}
	void add(int node, int i, int j, int l, int r, int u, int w) {
		if(i > r || j < l)
			return;
		if(i >= l && j <= r)
			return (void)(g[u].pb({node+n, w}));
		int m = (i+j) >> 1;
		add(2*node, i, m, l, r, u, w); add(2*node+1, m+1, j, l, r, u, w);
	}
} s1;

struct SegSobe
{
	void build(int node, int i, int j) {
		if(i == j)
			g[i].pb({node+max_node, 0});
		else {
			int m = (i+j) >> 1;
			build(2*node, i, m); build(2*node+1, m+1, j);
			g[2*node+max_node].pb({node+max_node, 0});
			g[2*node+1+max_node].pb({node+max_node, 0});
		}
	}
	void add(int node, int i, int j, int l, int r, int u, int w) {
		if(i > r || j < l)
			return;
		if(i >= l && j <= r)
			return (void)(g[node+max_node].pb({u, w}));
		int m = (i+j) >> 1;
		add(2*node, i, m, l, r, u, w); add(2*node+1, m+1, j, l, r, u, w);
	}
} s2;

bool mark[maxn];

ll dist[maxn];

void dijkstra(int s) {
	for(int i = 1; i < maxn; i++)
		dist[i] = inf;
	dist[s] = 0;

	priority_queue<pli, vector<pli>, greater<pli>> q;
	q.push({0, s});

	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(pii pp : g[u]) {
			int v = pp.ff, w = pp.ss;
			if(dist[v] > dist[u] + 1ll*w) {
				dist[v] = dist[u] + 1ll*w;
				q.push({dist[v], v});
			}
		}
	}
}

int main() {
	int q, s; scanf("%d %d %d", &n, &q, &s);
	s1.build(1, 1, n);
	s2.build(1, 1, n);
	while(q--) {
		int t; scanf("%d", &t);
		if(t == 1) {
			int u, v, w; scanf("%d %d %d", &u, &v, &w);
			g[u].pb({v, w});
		}
		else {
			int u, l, r, w; scanf("%d %d %d %d", &u, &l, &r, &w);
			if(t == 2)
				s1.add(1, 1, n, l, r, u, w);
			else
				s2.add(1, 1, n, l, r, u, w);
		}
	}

	dijkstra(s);
	for(int i = 1; i <= n; i++)
		printf("%lld ", dist[i]<inf?dist[i]:-1);
	printf("\n");
}