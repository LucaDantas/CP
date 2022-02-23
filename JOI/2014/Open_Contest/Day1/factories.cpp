#include "factories.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10, logn = 21;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

vector<pair<int,long long>> g[maxn];

int in[maxn], pai[logn][maxn], profundidade[maxn], t, n;
long long depth[maxn];

void dfs(int u) {
	in[u] = ++t;
	for(auto [v, w] : g[u])
		if(v != pai[0][u])
			pai[0][v] = u, depth[v] = depth[u] + w, profundidade[v] = profundidade[u] + 1, dfs(v);
}

void build_binary_lifting() {
	for(int l = 1; l < logn; l++) {
		for(int i = 1; i < maxn; i++) {
			pai[l][i] = pai[l-1][pai[l-1][i]];
		}
	}
}

int LCA(int a, int b) {
	if(profundidade[a] < profundidade[b]) swap(a, b);
	for(int l = logn-1; l >= 0; l--) {
		if(profundidade[a] - (1 << l) >= profundidade[b])
			a = pai[l][a];
	}
	if(a == b) return a;
	for(int l = logn-1; l >= 0; l--) {
		if(pai[l][a] != pai[l][b])
			a = pai[l][a], b = pai[l][b];
	}
	return pai[0][a];
}

long long dist(int a, int b) { return depth[a] + depth[b] - 2*depth[LCA(a, b)]; }

vector<pair<int, long long>> vt[maxn];

void get_vt(vector<int>& v) {
	sort(v.begin(), v.end(), [](int a, int b) { return in[a] < in[b]; });
	
	int tam = v.size();
	for(int i = 1; i < tam; i++)
		v.push_back(LCA(v[i-1], v[i]));

	sort(v.begin(), v.end(), [](int a, int b) { return in[a] < in[b]; });
	v.erase(unique(v.begin(), v.end()), v.end());
	
	for(int x : v)
		vt[x].clear();

	for(int i = 1; i < v.size(); i++) {
		int lca = LCA(v[i-1], v[i]);
		long long DIST = depth[v[i]] - depth[lca];
		vt[lca].push_back({v[i], DIST});
		vt[v[i]].push_back({lca, DIST});
	}
}

void Init(int32_t N, int32_t A[], int32_t B[], int32_t D[]) {
	n = N;
	for(int i = 0; i < n-1; i++) {
		A[i]++, B[i]++;
		g[A[i]].push_back({B[i], D[i]}), g[B[i]].push_back({A[i], D[i]});
	}
	profundidade[1] = 1;
	depth[1] = 1;
	dfs(1);
	build_binary_lifting();
}

long long dd[maxn];
bool mark[maxn];

long long dijkstra(const vector<int>& tudo, const vector<int>& X, const vector<int>& Y) {
	static priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q;
	for(int x : tudo)
		dd[x] = inf, mark[x] = 0;
	for(int x : Y)
		dd[x] = 0, q.push({0, x});

	while(q.size()) {
		int u = q.top().second;
		q.pop();
		if(mark[u]) continue;
		mark[u] = 1;

		for(auto [v, w] : vt[u])
			if(dd[v] > dd[u] + w)
				dd[v] = dd[u] + w, q.push({dd[v], v});
	}

	long long ans = inf;
	for(int x : X)
		ans = min(ans, dd[x]);
	return ans;
}

long long Query(int32_t S, int32_t X[], int32_t T, int32_t Y[]) {
	vector<int> v, x, y;
	for(int i = 0; i < S; i++)
		v.push_back(X[i]+1), x.push_back(X[i]+1);
	for(int i = 0; i < T; i++)
		v.push_back(Y[i]+1), y.push_back(Y[i]+1);
	get_vt(v);
	return dijkstra(v, x, y);
}

