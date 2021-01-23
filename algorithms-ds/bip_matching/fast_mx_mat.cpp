/*
	Hopcroft-Karp algorithm for maximum bipartite matching
	Complexity: O(sqrt(n)*m)
*/

#include<bits/stdc++.h>
using namespace std;
 
using pii = pair<int,int>;
 
#define pb push_back
 
constexpr int maxn = 1e5+10;
 
int color[maxn], match[maxn], dist[maxn];
bool mark[maxn];
 
vector<int> g[maxn];
 
bool dfs(int u) {
	mark[u] = 1;
 
	if(color[u]) {
		if(match[u])
			return dist[match[u]] == dist[u]+1 && dfs(match[u]);
		return 1;
	}
 
	for(int v : g[u]) {
		if(mark[v] || dist[v] != dist[u]+1 || !dfs(v)) continue;
		match[u] = v, match[v] = u;
		return 1;
	}
 
	return 0;
}
 
bool bfs(int n) {
	memset(mark, 0, sizeof mark);
	memset(dist, 0, sizeof dist);
	queue<int> q;
 
	for(int i = 1; i <= n; i++)
		if(!color[i] && !match[i]) q.push(i), mark[i] = 1;
	
	int lim = maxn;
 
	while(q.size() && dist[q.front()] <= lim) {
		int u = q.front(); q.pop();
 
		if(color[u]) {
			if(!match[u]) lim = dist[u];
			else if(!mark[match[u]]) dist[match[u]] = dist[u]+1, q.push(match[u]);
			continue;
		}
 
		for(int v : g[u]) {
			if(mark[v]) continue;
			mark[v] = 1;
			dist[v] = dist[u]+1;
			q.push(v);
		}
	}

	return lim != maxn;
}

int hk(int n) {
	int ans = 0;
	while(bfs(n)) {
		memset(mark, 0, sizeof mark);

		for(int i = 1; i <= n; i++)
			if(!color[i] && !match[i] && !mark[i])
				ans += dfs(i);
	 
	}
	return ans;
}

int main() {
	int n, m, p; scanf("%d %d %d", &n, &m, &p);
	
	for(int i = 0, a, b; i < p; i++)
		scanf("%d %d", &a, &b), g[a].pb(b+n), g[b+n].pb(a);

	for(int i = 1; i <= n; i++)
		color[i] = 1;

	printf("%d\n", hk(n+m));
}