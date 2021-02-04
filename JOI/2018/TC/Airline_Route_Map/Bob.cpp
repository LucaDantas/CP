#include "Boblib.h"
#include<vector>
#include <cassert>
#include <cstdio>

#define pb push_back

constexpr int maxn = 1510;

std::vector<int> g[maxn];

int val[maxn];

bool mark[maxn], vis[maxn];

void Bob( int V, int U, int C[], int D[] ){
	for(int i = 0; i < U; i++)
		g[C[i]].pb(D[i]), g[D[i]].pb(C[i]);
	std::vector<int> opa;
	int mx = -1;
	for(int i = 0; i < V; i++)
		if((int)g[i].size() == 1)
			opa.pb(i);

	int N = V-12;
	for(int x : opa) {
		if((int)g[g[x][0]].size() == N+1)
			mx = g[x][0];
	}

	for(int v : g[mx])
		mark[v] = 1;

	std::vector<int> a, b;
	for(int i = 0; i < V; i++)
		if(!mark[i] && i != mx)
			a.pb(i);

	for(int x : a) {
		int cnt = 0;
		for(int v : g[x])
			if(!mark[v]) ++cnt;
		if(cnt == 1) b.pb(x);
	}

	int now = -1;
	if(g[b[0]].size() > g[b[1]].size())
		now = b[0];
	else now = b[1];

	int pos = 0;
	while(1) {
		for(int v : g[now])
			if(mark[v]) val[v] += 1<<pos, --U;
		++pos;
		int ok = 0;
		vis[now] = 1;
		for(int v : g[now])
			if(!mark[v] && !vis[v]) {now = v; ok = 1; break;}
		if(!ok) break;
	}
	InitMap(N, U - N - 10);
	for(int i = 0; i < V; i++) {
		if(!val[i]) continue;
		for(int v : g[i])
			if(val[v] && val[i] > val[v])
				MakeMap(val[i]-1, val[v]-1);
	}
}

