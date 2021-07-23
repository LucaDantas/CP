// 70 pts
#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
 
using pii = pair<int,int>;
 
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()
#define ff first
#define ss second
 
constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 8e5 + 10;
 
mt19937 rng(random_device{}());
 
vector<int> g[maxn];
 
int match[maxn];
bool mark[maxn];
 
int t, n, qtd_ruas;
 
bool dfs(int u) {
	mark[u] = 1;
	if(u >= qtd_ruas) return (match[u] == -1 ? 1 : dfs(match[u]));
 
	for(int v : g[u]) {
		if(mark[v] || !dfs(v)) continue;
		match[u] = v; match[v] = u;
		return 1;
	}
 
	return 0;
}
 
struct Road { // todas as ruas possiveis
	int x, y, tipo; // ponto inicial da rua e se é vertical ou horizontal
} ruas[maxn];
 
pii conecta[maxn];
 
struct Banco {
	int x, y;
} bancos[maxn];
 
map<pair<int,int>, int> mp; // salva o id dos pontos
 
inline void add(int a, int b) { g[a].pb(b), g[b].pb(a); }
 
int get(pii p) { 
	if(mp.count(p)) return mp[p];
	bancos[t] = {p.ff, p.ss};
	return mp[p] = t++;
}
 
bool mark2[maxn];
int vis = 0;
 
void vai(int x, int y) {
	++vis;
	int id = mp[pii(x, y)];
	mark2[id] = 1;
	if(mp.count({x+2, y}) && !mark2[mp[pii(x+2, y)]]) {
		conecta[t] = {id, mp[pii(x+2, y)]};
		ruas[t++] = {x, y, 0};
		vai(x+2, y);
	}
	if(mp.count({x-2, y}) && !mark2[mp[pii(x-2, y)]]) {
		conecta[t] = {mp[pii(x-2, y)], id};
		ruas[t++] = {x-2, y, 0};
		vai(x-2, y);
	}
	if(mp.count({x, y+2}) && !mark2[mp[pii(x, y+2)]]) {
		conecta[t] = {id, mp[pii(x, y+2)]};
		ruas[t++] = {x, y, 1};
		vai(x, y+2);
	}
	if(mp.count({x, y-2}) && !mark2[mp[pii(x, y-2)]]) {
		conecta[t] = {id, mp[pii(x, y-2)]};
		ruas[t++] = {x, y-2, 1};
		vai(x, y-2);
	}
}
 
int construct_roads(vector<int> x, vector<int> y) {
	n = sz(x);
	for(int i = 0; i < n; i++)
		mp[pii(x[i], y[i])] = i;
	vai(x[0], y[0]);
	if(vis != n) return 0; // impossivel, o grafo completo não é conexo
	
	qtd_ruas = t;
	for(int i = 0; i < qtd_ruas; i++) {
		auto [X, Y, tipo] = ruas[i];
		if(!tipo) {
			int aq = get({X+1, Y+1});
			add(i, aq);
 
			aq = get({X+1, Y-1});
			add(i, aq);
		} else {
			int aq = get({X+1, Y+1});
			add(i, aq);
 
			aq = get({X-1, Y+1});
			add(i, aq);
		}
	}
 
	int ans = 0;
	memset(match, -1, sizeof match);
 
	vector<int> p(qtd_ruas); iota(all(p), 0);
 
	for(int i = 0; i < t; i++)
		shuffle(all(g[i]), rng);
 
	for(int antes = -1; ans != antes;) {
		antes = ans;
		memset(mark, 0, sizeof mark);
		shuffle(all(p), rng);
		for(int i = 0; i < qtd_ruas; i++)
			if(!mark[p[i]] && match[p[i]] == -1 && dfs(p[i])) ++ans;
	}
 
	if(ans != qtd_ruas) return 0;
	
	vector<int> u(qtd_ruas), v(qtd_ruas), a(qtd_ruas), b(qtd_ruas);
 
	for(int i = 0; i < qtd_ruas; i++) {
		u[i] = conecta[i].ff, v[i] = conecta[i].ss;
		a[i] = bancos[match[i]].x, b[i] = bancos[match[i]].y;
	}
	build(u, v, a, b);
	return 1;
}
