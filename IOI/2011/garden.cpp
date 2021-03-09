#include "garden.h"
#include "gardenlib.h"
#include<vector>
#include<cstdio>
#include<cstring>

constexpr int maxn = 3e5+10;

std::vector<int> g[maxn]; // functional graph reversed
int f[maxn], s[maxn], dist[maxn][2], ans[maxn][2], last[maxn][2], n, sz[2];
bool mark[maxn];

void dfs(int u, int d, int k, int p) {
	if(u < n/2) ++dist[d][k];
	for(int v : g[u])
		if(v != p) dfs(v, d+1, k, p);
}

void dfs2(int u, int k, int p) {
	mark[u] = 1; ++sz[k];
	if(f[u] == p) return;
	if(mark[f[u]]) return (void)(sz[k] = maxn);
	dfs2(f[u], k, p);
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]) {
	n = 2*N;
	for(int i = 0; i < n; i++)
		f[i] = s[i] = -1;
	for(int i = 0; i < M; i++) {
		int a = R[i][0], b = R[i][1];
		
		if(f[a] == -1) f[a] = b;
		else if(s[a] == -1) s[a] = b;

		if(f[b] == -1) f[b] = a;
		else if(s[b] == -1) s[b] = a;
	}
	
	for(int a = 0; a < N; a++) {
		if(s[a] == -1) s[a] = f[a];
		if(f[f[a]] == a) g[f[a]+N].push_back(a);
		else g[f[a]].push_back(a);
		if(f[s[a]] == a) g[s[a]+N].push_back(a+N);
		else g[s[a]].push_back(a+N);
	}

	for(int i = 0; i < n; i++)
		for(int v : g[i]) f[v] = i;
	
	dfs(P, 0, 0, P);

	dfs(P+N, 0, 1, P+N);

	dfs2(P, 0, P);
	memset(mark, 0, sizeof mark);
	dfs2(P+N, 1, P+N);

	for(int b = 0; b <= 1; b++) {
		for(int i = 0; i < n; i++) {
			ans[i][b] = (i>=sz[b]?ans[i-sz[b]][b]:0) + dist[i][b];
			last[i%sz[b]][b] = i;
		}
	}
	for(int i = 0; i < Q; i++) {
		int here = 0;
		for(int b = 0; b <= 1; b++)
			if(sz[b] < maxn) here += ans[std::min(G[i], last[G[i]%sz[b]][b])][b];
			else if(G[i] < n) here += dist[G[i]][b];
		answer(here);
	}
}
