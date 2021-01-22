#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 5e4+10;

vector<int> g[maxn];

int color[maxn], edge_match[maxn];
bool mark[maxn], match[maxn];

bool dfs(int u) {
	mark[u] = 1;

	if(color[u]) {
		if(match[u])
			return dfs(edge_match[u]);
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v] || !dfs(v)) continue;
		match[u] = match[v] = 1;
		edge_match[u] = v, edge_match[v] = u;
		return 1;
	}

	return 0;
}

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		vector<int> ultimo(n);
		iota(ultimo.begin(), ultimo.end(), 0);
		int now, ptr = n;
		for(int k = 0; k < n; k++) {
			now = ptr++; color[now] = 1;
			for(int i = 0; i < n; i++) {
				char c; scanf(" %c", &c);
				if(c == '.') g[now].pb(ultimo[i]), g[ultimo[i]].pb(now);
				else now = ptr++, color[now] = 1, ultimo[i] = ptr++;
			}
		}

		int ans = 0;
		for(int i = 0; i < ptr; i++) {
			if(color[i] || match[i]) continue;
			memset(mark, 0, sizeof mark);
			ans += dfs(i);
		}

		printf("%d\n", ans);

		for(int i = 0; i < ptr; i++)
			g[i].clear(), match[i] = 0, edge_match[i] = 0, color[i] = 0;
	}
}