#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pli = pair<ll,int>;

#define ff first
#define ss second
#define pb push_back
#define sz(a) (int)(a.size())

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

int n, depth[maxn], pai[maxn][20];

bool traste[maxn];

vector<int> extra;

vector<pii> tree[maxn], g[maxn];

ll dist[maxn][45], tab[maxn][20];

bool mark[maxn];

void dijkstra(int s, int k) {
	for(int i = 0; i < maxn; i++)
		dist[i][k] = inf;
	dist[s][k] = 0;

	memset(mark, 0, sizeof mark);

	priority_queue<pli, vector<pli>, greater<pli>> q;
	q.push({0, s});

	while(q.size()) {
		int u = q.top().ss; q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(pii pp : g[u]) {
			int v = pp.ff, w = pp.ss;
			if(dist[v][k] > dist[u][k] + 1ll*w) {
				dist[v][k] = dist[u][k] + 1ll*w;
				q.push({dist[v][k], v});
			}
		}
	}
}

void dfs(int u, int p, int d=1) {
	depth[u] = d;
	for(pii pp : tree[u]) {
		int v = pp.ff, w = pp.ss;
		if(v == p) continue;
		tab[v][0] = w;
		pai[v][0] = u;
		dfs(v, u, d+1);
	}
}

void compute() {
	for(int l = 1; l < 20; l++) {
		for(int i = 1; i <= n; i++) {
			pai[i][l] = pai[pai[i][l-1]][l-1];
			tab[i][l] = tab[i][l-1] + tab[pai[i][l-1]][l-1];
		}
	}
}

ll path(int a, int b) {
	if(a == b) return 0;
	if(depth[a] < depth[b])
		swap(a, b);
	ll ans = 0;
	for(int l = 19; l >= 0; l--)
		if(depth[pai[a][l]] >= depth[b])
			ans += tab[a][l], a = pai[a][l];
	if(a == b)
		return ans;
	for(int l = 19; l >= 0; l--)
		if(pai[a][l] != pai[b][l])
			ans += tab[a][l] + tab[b][l], a = pai[a][l], b = pai[b][l];
	assert(a != b && pai[a][0] == pai[b][0]);
	return ans + tab[a][0] + tab[b][0];
}

int main() {
	int m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int u, v, d; scanf("%d %d %d", &u, &v, &d);
		if(dsu.join(u, v)) {
			tree[u].pb({v, d});
			tree[v].pb({u, d});
		} else {
			if(!traste[u])
				extra.pb(u);
			if(!traste[v])
				extra.pb(v);
			traste[u] = traste[v] = 1;
		}
		g[u].pb({v, d});
		g[v].pb({u, d});
	}
	for(int i = 0; i < sz(extra); i++)
		dijkstra(extra[i], i);

	dfs(1, 0); // enraizar a árvore
	compute();

	int q; scanf("%d", &q);
	while(q--) {
		int u, v; scanf("%d %d", &u, &v);
		ll ans = path(u, v); // pela árvore
		for(int i = 0; i < sz(extra); i++)
			ans = min(ans, path(u, extra[i]) + dist[v][i]);
		printf("%lld\n", ans);
	}
}