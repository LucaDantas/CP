#include <bits/stdc++.h>
using namespace std;

#define int long long

using pii = pair<int, pair<int,int>>;

#define pb push_back
#define ff first
#define ss second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())

constexpr int inf = 0x3f3f3f3f3f3f3f;
constexpr int maxn = 6e5 + 10;

int dist[maxn], ans[maxn], TT;

bool mark[maxn];

vector<pii> g[maxn];

struct Edge
{
	int a, b, c, id;
	bool operator<(const Edge& o) const { 
		if(c != o.c) return c < o.c;
		return id < o.id;
	}
};

bool forbidden[maxn];

void dijkstra_mx(int s) {
	memset(dist, 0x3f, sizeof dist);
	memset(mark, 0, sizeof mark);
	dist[s] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
	q.push({0, s});
	while(q.size()) {
		int u = q.top().second; q.pop();
		if(mark[u]) continue;

		mark[u] = 1;
		for(pii pp : g[u]) {
			int v = pp.ff, w = pp.ss.ff, id = pp.ss.ss;
			if(forbidden[id]) continue;
			if(dist[v] > max(w, dist[u]))
				dist[v] = max(w, dist[u]), q.push({max(w, dist[u]), v});
		}
	}
}

void dfs_subtask(int u, int p, pair<int,int> vls) {
	dist[u] = vls.ff + vls.ss;
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss.ff;
		if(v == p) continue;
		pair<int,int> here = vls;
		here.first = max(here.first, w);
		here.second = min(here.second, w);
		dfs_subtask(v, u, here);
	}
}

struct DSU
{
	int pai[maxn], peso[maxn];

	DSU() {
		for(int i = 0; i < maxn; i++) {
			pai[i] = i;
			peso[i] = 1;
		}
	}

	int find(int x) {
		if(pai[x] == x) return x;
		return pai[x] = find(pai[x]);
	}

	bool join(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return 0;

		if(peso[x] < peso[y]) swap(x,y);

		peso[x] += peso[y];
		pai[y] = x;
		return 1;
	}
} dsu;

vector<Edge> edges;

vector<pii> tree[maxn];

void dfs(int u, int p, int mn_here, int mx_here, int n) {
	dijkstra_mx(u);
	for(int i = 2; i <= n; i++)
		ans[i] = min(ans[i], max(mx_here, dist[i]) + mn_here);

	for(pii pp : tree[u]) {
		int v = pp.ff, w = pp.ss.ff, id = pp.ss.ss;
		if(v == p) continue;
		forbidden[id] = 1;
		dfs(v, u, min(mn_here, w), max(mx_here, w), n);
		forbidden[id] = 0;
	}
}

int32_t main() {
	int n, m; scanf("%lld %lld", &n, &m);
	for(int i = 0, u, v, w; i < m; i++)
		scanf("%lld %lld %lld", &u, &v, &w), g[u].pb({v, {w, ++TT}}), g[v].pb({u, {w, TT}}), edges.pb({u, v, w, TT});
	int mx = 0;
	for(pii pp : g[1])
		mx = max(mx, pp.ss.ff);
	if(mx == 0) {
		// s2
		dijkstra_mx(1);
		for(int i = 2; i <= n; i++)
			printf("%lld\n", dist[i]);
	} else if(m == n-1) {
		// s1
		dfs_subtask(1, 0, {0, inf});
		for(int i = 2; i <= n; i++)
			printf("%lld\n", dist[i]);
	} else {
		if(n > 2000) assert(0);
		for(int i = 1; i <= n; i++)
			ans[i] = inf;
		sort(all(edges));
		for(auto e : edges) {
			int u = e.a, v = e.b, w = e.c, id = e.id;
			if(dsu.join(u, v))
				tree[u].pb({v, {w, id}}), tree[v].pb({u, {w, id}});
		}
		dfs(1, 0, inf, 0, n);
		for(int i = 2; i <= n; i++)
			printf("%lld\n", ans[i]);
	}
}
