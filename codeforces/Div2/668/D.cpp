#include<bits/stdc++.h>
using namespace std;

// if b <= 2*a a wins, if b > 2*a and he can reach two points of distance 
// at least 2*a+1 between them b wins, otherwise a wins

constexpr int maxn = 1e5+10;

#define pb push_back

bool mark[maxn];
int depth[maxn], fundo[maxn], dist[maxn];
vector<int> g[maxn];

void dfs(int u, int p, int d) {
	depth[u] = fundo[u] = d;
	for(auto v : g[u]) {
		if(v != p) {
			dfs(v, u, d+1);
			if(fundo[v] > fundo[u]) {
				fundo[u] = fundo[v];
			}
		}
	}
}

void bfs(int s) {
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		mark[u] = 1;
		for(auto v : g[u]) {
			if(!mark[v]) {
				dist[v] = dist[u]+1;
				q.push(v);
			}
		}
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, a, b, da, db; scanf("%d %d %d %d %d", &n, &a, &b, &da, &db);
		for(int i = 0; i <= n+5; i++) {
			fundo[i] = depth[i] = dist[i] = mark[i] = 0;
			g[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int u, v; scanf("%d %d", &u, &v);
			g[u].pb(v); g[v].pb(u);
		}
		dfs(a, 0, 0);
		if(depth[b] <= da || db <= 2*da) {
			puts("Alice"); continue;
		}

		bfs(a);

		int best = max_element(dist+1, dist+1+n) - dist;

		for(int i = 0; i <= n+5; i++) mark[i] = 0;
		bfs(best);
		if(*max_element(dist+1, dist+1+n) > 2*da) {
			puts("Bob");
		} else puts("Alice");
	}
}