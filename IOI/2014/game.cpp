#include "game.h"
#include<vector>

#define pb push_back
#define sz(a) (int)((a).size())

constexpr int maxn = 1510;

struct DSU
{
	int pai[maxn]; std::vector<int> grp[maxn];
	void init(int n) {
		for(int i = 0; i < n; i++)
			pai[i] = i, grp[i].pb(i);
	}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	std::vector<int> get(int x) {return grp[find(x)];}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(sz(grp[a]) < sz(grp[b]))
			std::swap(a, b);
		pai[b] = a;
		for(int x : grp[b])
			grp[a].pb(x);
		grp[b].clear();
	}
} dsu;

int mark[maxn][maxn];

void initialize(int n) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			mark[i][j] = -1;
	dsu.init(n);
}

int hasEdge(int u, int v) {
	if(u > v) std::swap(u, v);
	std::vector<int> a = dsu.get(u), b = dsu.get(v);
	mark[u][v] = 0;
	for(int x : a) {
		for(int y : b) {
			if(mark[std::min(x,y)][std::max(x,y)] == -1)
				return 0;
		}
	}
	dsu.join(u, v);
	mark[u][v] = 1;
	return 1;
}
