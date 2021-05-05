#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())

constexpr int maxn = 1e3+10; // O(nm)

vector<int> g[maxn];

int color[maxn], edge_match[maxn], s, n, m;

bool mark[maxn], match[maxn];

int dfs(int u, int p) {
	mark[u] = 1;
	if(color[u] && !match[u]) {
		edge_match[u] = p;
		match[u] = 1;
		return 1;
	}
	
	if(color[u] && match[u]) {
		int ans = dfs(edge_match[u], u);
		if(ans == 0) return 0;
		edge_match[u] = p;
		match[u] = 1;
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v] || color[u] == color[v] || v == s) continue;
		int ans = dfs(v, u);
		if(ans == 0) continue;
		edge_match[u] = v;
		match[u] = 1;
		return 1;
	}
	return 0;
}

int matching() {
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(color[i] || match[i] || i == s) continue;
		memset(mark, 0, sizeof mark);
		ans += dfs(i, 0);
	}
	return ans;
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb(b), g[b].pb(a);
	}

	for(int i = 1; i <= n; i++) {
		s = i;
		if(2*sz(g[s]) < n-1) continue;
		memset(color, 0, sizeof color);
		memset(match, 0, sizeof match);
		memset(edge_match, 0, sizeof edge_match);
		color[s] = 1;
		for(int u : g[s])
			color[u] = 1;
		for(int u : g[s])
			for(int v : g[u])
				if(!color[v]) color[v] = 2;
		bool ok = 1;
		for(int u = 1; u <= n; u++) {
			if(!color[u]) {ok = 0; break;}
			--color[u];
		}
		if(ok) {
			int ans = matching(), opa = -1;
			for(int u = 1; u <= n; u++)
				if(!match[u]) ++opa;
			if(ans == n-1-sz(g[s])) printf("Yes\n%d %d\n", s, ans+opa);
			else continue;
			for(int u = 1; u <= n; u++) {
				if(u == s) continue;
				if(color[u] && match[u])
					printf("%d %d\n", u, edge_match[u]);
				if(!match[u])
					printf("%d -1\n", u);
			}
			return 0;
		}
	}
	puts("No");
}
