#include<bits/stdc++.h>
#include "grader.h"
#include "decoder.h"

using namespace std;

#define pb push_back

constexpr int maxn = 1e3+10;

static int pai[maxn], dist[maxn], f[maxn];

static vector<int> g[maxn];

bool mark[maxn];

void dfs_ans(int u) {
	mark[u] = 1;
	if(!mark[pai[u]])
		dist[pai[u]] = dist[u] + f[u], dfs_ans(pai[u]);
	for(int v : g[u]) {
		if(mark[v]) continue;
		dist[v] = dist[u] - f[v];
		dfs_ans(v);
	}
}

void decode(int N, int H) {
	for(int i = 1; i < N; i++) {
		for(int j = 0; j < 10; j++)
			pai[i] += decode_bit()<<j;
		g[pai[i]].pb(i);
	}
	for(int i = 0; i < H; i++) {
		for(int j = 1; j < N; j += 3) {
			int p = 0;
			for(int k = 0; k < 5; k++)
				p += decode_bit()<<k;
			int pot[] = {1, 3, 9, 27};
			for(int k : {0, 1, 2})
				f[j+k] = ((p%pot[k+1])/pot[k])-1;
		}
		dfs_ans(i);
		for(int j = 0; j < N; j++)
			hops(i, j, dist[j]);
		memset(f, 0, sizeof f);
		memset(dist, 0, sizeof dist);
		memset(mark, 0, sizeof mark);
	}
}
