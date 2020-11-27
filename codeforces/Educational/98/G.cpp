#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

// Get the centroid and from it get the best guy that stands at every
// distance possible and the update the guys on each side that way

vector<int> g[maxn];

int d[maxn], gld[maxn];

void bfs(vector<int>& rapa) {
	queue<int> q;
	for(int x : rapa)
		q.push(x), gld[x] = 1;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int v : g[u])
			if(!gld[v])
				gld[v] = 1, q.push(v), d[v] = d[u]+1;
	}
}

struct Centroid
{
	int sz[maxn], mark[maxn], here[maxn], ans[maxn], dist[maxn];
	vector<int> opa;
	void dfs(int u, int p = -1) {
		sz[u] = 1;
		for(int v : g[u])
			if(!mark[v] && v != p)
				dfs(v, u), sz[u] += sz[v];
	}
	int find(int u, int p, int tam) {
		for(int v : g[u])
			if(!mark[v] && v != p && 2*sz[v] > tam)
				return find(v, u, tam);
		return u;
	}
	void calc(int u, int p, int tam) {
		opa.pb(u);
		if(d[u] > dist[u])
			here[min(tam, d[u]-dist[u]-1)] = max(here[min(tam, d[u]-dist[u]-1)], d[u]);
		for(int v : g[u])
			if(!mark[v] && v != p)
				dist[v] = dist[u]+1, calc(v, u, tam);
	}
	void decompose(int u) {
		dfs(u); int tam = sz[u];
		u = find(u, -1, tam);
		mark[u] = 1; here[0] = d[u]; dist[u] = 0;
		for(int i = 0; i <= tam; i++)
			here[i] = 0;
		calc(u, -1, tam);
		for(int i = tam-1; i >= 0; i--)
			here[i] = max(here[i], here[i+1]);
		for(int x : opa)
			ans[x] = max(ans[x], here[dist[x]]);
		opa.clear();
		for(int v : g[u])
			if(!mark[v])
				decompose(v);
	}
} cent;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	
	int k; scanf("%d", &k);
	vector<int> rapa(k);
	for(int& x : rapa)
		scanf("%d", &x);
	bfs(rapa);
	
	cent.decompose(1);

	for(int i = 1; i <= n; i++)
		printf("%d ", cent.ans[i]);
	printf("\n");
}