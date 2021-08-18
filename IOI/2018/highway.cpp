#include "highway.h"
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define pb push_back

constexpr int maxn = 90010;

struct Edge { int v, id; };

vector<Edge> g[maxn], tree[maxn][2];
vector<int> ord[2], arv[2];
int pai[maxn];

int dist[maxn][2];
Edge P[maxn][2];
long long SZ; int M, edge;

void bfs(int s, int k) {
	queue<int> q;
	dist[s][k] = 0;
	q.push(s);

	while(q.size()) {
		int u = q.front(); q.pop();
		for(Edge E : g[u]) {
			if(dist[E.v][k] == -1) {
				dist[E.v][k] = dist[u][k] + 1;
				P[E.v][k] = {u, E.id};
				q.push(E.v);
			}
		}
	}
}

void dfs(int u, int k, int p = -1) {
	for(Edge E : tree[u][k]) {
		int v = E.v, id = E.id;
		if(p == v) continue;
		dfs(v, k, u);
		pai[v] = id;
	}
	ord[k].pb(u);
}

int get(int k) {
	int l = 0, r = (int)(ord[k].size()) - 2, ans = ord[k].back();

	while(l <= r) {
		int m = (l+r) >> 1;
		
		vector<int> w(M, 1);
		for(int x : arv[!k])
			w[x] = 0;
		for(int x : arv[k])
			w[x] = 0;
		w[edge] = 0;

		for(int i = 0; i <= m; i++)
			w[pai[ord[k][i]]] = 1;

		long long aq = ask(w);

		if(aq > SZ) ans = ord[k][m], r = m-1;
		else l = m+1;
	}

	return ans;
}

void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
	M = (int)(U.size());
	vector<int> w(M);
	SZ = ask(w);

	edge = 0; int l = 0, r = M-1;
	while(l <= r) {
		int m = (l+r) >> 1;
		for(int k = 0; k <= m; k++)
			w[k] = 1;
		long long aq = ask(w);
		if(aq > SZ) edge = m, r = m-1;
		else l = m+1;
		for(int& x : w) x = 0;
	}

	for(int i = edge; i < M; i++) {
		g[U[i]].pb({V[i], i});
		g[V[i]].pb({U[i], i});
	}

	memset(dist, -1, sizeof dist);
	bfs(U[edge], 0);
	bfs(V[edge], 1);

	for(int i = 0; i < N; i++) {
		if(dist[i][0] == dist[i][1] || i == U[edge] || i == V[edge]) continue;
		int k = dist[i][1] < dist[i][0];
		tree[i][k].pb(P[i][k]);
		tree[P[i][k].v][k].pb({i, P[i][k].id});
		arv[k].pb(P[i][k].id);
	}

	dfs(U[edge], 0);
	dfs(V[edge], 1);

	answer(get(1), get(0));
}
