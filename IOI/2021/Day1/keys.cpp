#include "keys.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 3e5 + 10;

struct DSU {
	int pai[maxn], peso[maxn];
	vector<int> validos[maxn];
	set<int> cores[maxn];
	map<int,vector<int>> g[maxn];
	
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }

	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b]) swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];

		for(int c : cores[b]) {
			cores[a].insert(c);

			if(!g[a].count(c)) continue;
			vector<int>& vt = g[a][c];

			for(int x : vt)
				validos[a].pb(x);

			g[a].erase(c);
		}
		cores[b].clear();
		
		for(int v : validos[b])
			validos[a].push_back(v);
		validos[b].clear();

		for(auto it : g[b]) {
			if(!cores[a].count(it.first))
				for(auto k : it.second)
					g[a][it.first].pb(k);
			else
				for(auto k : it.second)
					validos[a].pb(k);
		}
		g[b].clear();
	}
	int siz(int u) { return peso[find(u)]; }
} dsu;

int ans = inf;

int vis[maxn];
bool bom[maxn];

vector<int> cm;

void dfs(int u) {
	vis[u] = 1;
	cm.push_back(u);
	while(sz(dsu.validos[u])) {
		int v = dsu.find(dsu.validos[u].back());
		dsu.validos[u].pop_back();
		
		if(v == u) continue;
		if(vis[v] == 2) return (void)(vis[u] = 2);

		if(vis[v] == 1) {
			while(cm.back() != v)
				dsu.join(u, cm.back()), cm.pop_back();
			dsu.join(u, v);

			dfs(dsu.find(u));
			return;
		} else {
			dfs(dsu.find(v));
			vis[u] = 2;
			return;
		}
	}
	ans = min(ans, dsu.peso[u]);
	bom[u] = 1;
	vis[u] = 2;
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c) {
	vector<int> resp(r.size(), 0);

	int n = (int)(r.size()), m = (int)(u.size());

	for(int i = 0; i < n; i++)
		dsu.cores[i] = {r[i]};
	
	for(int i = 0; i < m; i++)
		for(int rep = 0; rep < 2; rep++, swap(u[i], v[i]))
			if(r[u[i]] == c[i]) dsu.validos[u[i]].pb(v[i]);
			else dsu.g[u[i]][c[i]].pb(v[i]);

	for(int i = 0; i < n; i++) if(!vis[dsu.find(i)]) dfs(i);

	for(int i = 0; i < n; i++)
		if(bom[dsu.find(i)] && dsu.siz(i) == ans) resp[i] = 1;
	return resp;
}
