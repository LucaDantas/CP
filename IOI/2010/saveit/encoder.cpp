#include<bits/stdc++.h>
#include "grader.h"
#include "encoder.h"

using namespace std;

#define pb push_back

constexpr int maxn = 1e3+10;

static int pai[maxn], dist[maxn];

static vector<int> g[maxn];

bool on(int a, int b) {return a&(1<<b);}

void dfs(int u) {
	dist[u] = 1;
	for(int v : g[u])
		if(!dist[v])
			pai[v] = u, dfs(v);
}

void encode(int N, int H, int M, int *A, int *B){
	for(int i = 0; i < M; i++)
		g[A[i]].pb(B[i]), g[B[i]].pb(A[i]);
	memset(pai, -1, sizeof pai);
	dfs(0);
	for(int i = 1; i < N; i++)
		for(int j = 0; j < 10; j++)
			encode_bit(on(pai[i], j));
	for(int i = 0; i < H; i++) {
		queue<int> q;
		for(int j = 0; j < N; j++)
			dist[j] = maxn;
		q.push(i);
		dist[i] = 0;

		while(q.size()) {
			int u = q.front(); q.pop();
			for(int v : g[u])
				if(dist[v] > dist[u]+1)
					q.push(v), dist[v] = dist[u]+1;
		}

		for(int j = 1; j < N; j += 3) {
			int pot[3] = {1, 3, 9}, p = 0;
			for(int k : {0, 1, 2})
				p += (dist[pai[j+k]]-dist[j+k]+1)*pot[k];
			for(int k = 0; k < 5; k++)
				encode_bit(on(p, k));
		}
	}
}
