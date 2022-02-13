// Subtask 2
#include "dungeons.h"
#include <vector>
#include <cstring>

constexpr int maxn = 4e5+10, logn = 25;
constexpr long long inf = 1e15L;

struct FunctionalGraph {
	int p[maxn], f[maxn];
	long long s[maxn];
	int tp[maxn];

	void add_edge(int i, int x, int v) { f[i] = x, p[i] = v; }
	void set_s(int i, long long st) { s[i] = st; tp[i] = st != inf; }

	bool in_cycle[maxn];
	int mark[maxn], prox_bom[maxn];
	long long dist_bom[maxn];

	void dfs(int u) {
		mark[u] = 1;

		if(mark[f[u]] == 1) {
			int fim = u; u = f[u]; in_cycle[fim] = 1;
			while(u != fim) in_cycle[u] = 1, u = f[u];
		}
		else if(!mark[f[u]]) dfs(f[u]);

		mark[u] = 2;
	}

	void dfs2(int u) {
		mark[u] = 1;
		if(!mark[f[u]]) dfs2(f[u]);
		dist_bom[u] = tp[u] ? 0 : dist_bom[f[u]] + p[u];
		prox_bom[u] = tp[u] ? u : prox_bom[f[u]];
	}

	void build(int n) {
		f[n] = n;
		s[n] = 0;
		p[n] = 0;
		tp[n] = 1;

		for(int i = 0; i <= n; i++)
			if(!mark[i]) dfs(i);
		
		memset(mark, 0, sizeof mark);
		for(int i = 0; i <= n; i++)
			if(!mark[i] && in_cycle[i] && tp[i]) {
				prox_bom[i] = i, dist_bom[i] = 0;
				dfs2(i);
			}

		for(int i = 0; i <= n; i++)
			if(!mark[i]) dfs2(i);
	}

	void go(int& x, long long& val) {
		val += dist_bom[x];
		x = prox_bom[x];

		if(val >= s[x]) return;

		val += p[x];
		x = f[x];

		go(x, val);
	}
} graph[logn];

int n;

void init(int N, std::vector<int> s, std::vector<int> p, std::vector<int> w, std::vector<int> l) {
	n = N;
	for(int lg = 0; lg < logn; lg++) {
		int lim = 1<<lg;

		for(int i = 0; i < n; i++) {
			if(s[i] <= lim) {
				graph[lg].add_edge(i, w[i], s[i]);
				graph[lg].set_s(i, inf);
			} else {
				graph[lg].add_edge(i, l[i], p[i]);
				graph[lg].set_s(i, s[i]);
			}
		}

		graph[lg].build(n);
	}

	return;
}

long long simulate(int x, int z) {
	long long val = z;
	for(int lg = 0; lg < logn; lg++)
		if(x != n) graph[lg].go(x, val);
	return val;
}

