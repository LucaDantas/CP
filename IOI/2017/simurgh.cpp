#include "simurgh.h"
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define ff first
#define ss second
#define sz(a) (int)(a.size())

constexpr int maxn = 510;

struct Edge
{
	int a, b, w, id; bool vis;
};

vector<Edge> arvore;

int n, m, t;
int depth[maxn];
pii pai[maxn];

vector<pii> g[maxn], meus[maxn];

void dfs(int u) {
	for(pii pp : g[u]) {
		auto [v, id] = pp;
		if(!depth[v]) {
			depth[v] = depth[u] + 1;

			arvore.pb({u, v, 0, id, 0});
			pai[v] = {u, t++};

			dfs(v);
		}
		else if(depth[v] > depth[u])
			meus[u].push_back(pp);
	}
}

void calc_tree() {
	vector<int> qry(n-1);
	for(int i = 0; i < t; i++)
		qry[i] = arvore[i].id;

	int base = count_common_roads(qry);

	for(int u = 0; u < n; u++) {
		if(!meus[u].size()) continue;

		for(auto [v, id] : meus[u]) {
			vector<int> ask, oto;

			for(int i = v; i != u; i = pai[i].ff) {
				int id_tree = pai[i].ss;
				if(!arvore[id_tree].vis) ask.push_back(id_tree), arvore[id_tree].vis = 1;
				else oto.push_back(id_tree);
			}

			if(!ask.size()) continue;

			if(oto.size()) {
				int e = oto.front();
				qry[e] = id;
				int eu = abs(count_common_roads(qry) - base) ^ arvore[e].w;
				qry[e] = arvore[e].id;

				for(const int& e : ask) {
					qry[e] = id;
					arvore[e].w = abs(count_common_roads(qry) - base) ^ eu;
					qry[e] = arvore[e].id;
				}
			} else {
				vector<int> ans;
				int mx = 0;
				for(int e : ask) {
					qry[e] = id;
					ans.pb(count_common_roads(qry) - base), mx = max(mx, ans.back());
					qry[e] = arvore[e].id;
				}

				int eu = mx;
				for(int i = 0; i < sz(ask); i++) {
					int e = ask[i];
					arvore[e].w = eu ^ abs(ans[i]);
				}
			}
		}
	}
}

struct DSU
{
	int pai[maxn], peso[maxn];
	void init() { for(int i = 0; i < n; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b]) swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return 1;
	}
} dsu;

pii edge[maxn*maxn];

int complete(vector<int>& base) {
	dsu.init();
	for(int x : base)
		dsu.join(edge[x].ff, edge[x].ss);
	int custo = 0;
	for(Edge x : arvore)
		if(dsu.join(x.a, x.b))
			custo += x.w, base.pb(x.id);
	return custo;
}

vector<int> ans;
void solve(int u, int l, int r, int val) {
	if(!val) return;
	if(l == r) return (void)(ans.pb(meus[u][l].ss));
	int m = (l+r) >> 1;
	vector<int> gld;
	for(int i = l; i <= m; i++)
		gld.pb(meus[u][i].ss);
	int b = complete(gld);

	b = count_common_roads(gld) - b;
	solve(u, l, m, b);
	solve(u, m+1, r, val-b);
}

vector<int> find_roads(int N, vector<int> U, vector<int> V) {
	n = N; m = (int)(U.size());
	for(int i = 0; i < m; i++) {
		g[U[i]].push_back({V[i], i});
		g[V[i]].push_back({U[i], i});
		edge[i] = {U[i], V[i]};
	}
	depth[0] = 1;

	dfs(0);

	calc_tree();

	for(auto& e : arvore) {
		e.w |= !e.vis;
		if(e.w) ans.pb(e.id);
	}

	for(int u = 0; u < n; u++) {
		if(!meus[u].size()) continue;
		vector<int> gld;
		for(auto p : meus[u])
			gld.pb(p.ss);
		int b = complete(gld);
		b = count_common_roads(gld) - b;
		solve(u, 0, sz(meus[u])-1, b);
	}

	return ans;
}