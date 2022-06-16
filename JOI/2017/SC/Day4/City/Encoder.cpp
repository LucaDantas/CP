#include "Encoder.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1<<18;
constexpr double base = 1.05; // uso os intervalos em tamanho de potencias dessa base

vector<int> g[maxn];

static vector<int> val;

void set_val() {
	val.push_back(1);
	for(int i = 1; i < (1 << 8); i++) {
		int aq = val.back() * base;
		if(aq == val.back()) ++aq;
		val.push_back(aq);
	}
}

int find_pot(int x) { return lower_bound(val.begin(), val.end(), x) - val.begin(); }

int dfs(int u, int p, int in) {
	int out = in+1;
	for(int v : g[u]) if(v != p)
		out = dfs(v, u, out);
	int sz = out - in, d = find_pot(sz);
	Code(u, (in<<8)|d);
	return in + val[d];
}

void Encode(int N, int A[], int B[])
{
	set_val();
	for(int i = 0; i < N-1; i++)
		g[A[i]].push_back(B[i]), g[B[i]].push_back(A[i]);
	dfs(0, -1, 0);
}
