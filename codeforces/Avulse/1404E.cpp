#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

int sv[210][210][4], last[210], ptr; // 0 -> t, 1 -> r, 2 -> d, 3 -> l

int dist[maxn], color[maxn], match[maxn];
bool mark[maxn];

vector<int> g[maxn];

bool dfs(int u) {
	mark[u] = 1;

	if(color[u])
		return !match[u] || dfs(match[u]);

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
		if(!color[i] && !match[i])
			q.push(i), mark[i] = 1;

	int lim = maxn;

	while(!q.empty() && dist[q.front()] <= lim) {
		int u = q.front(); q.pop();

		if(color[u]) {
			if(!match[u]) lim = dist[u];
			else assert(!mark[match[u]]), dist[match[u]] = dist[u]+1, q.push(match[u]);
			continue;
		}

		for(int v : g[u]) {
			if(!mark[v]) {
				mark[v] = 1;
				dist[v] = dist[u]+1;
				q.push(v);
			}
		}
	}

	return lim != maxn;
}

int hk(int n) {
	int ans = 0;
	while(bfs(n)) {
		memset(mark, 0, sizeof mark);

		for(int i = 1; i <= n; i++) {
			if(!color[i] && !mark[i] && !match[i])
				ans += dfs(i);
		}
	}

	return ans;
}

int main() {
	int n, m, qtd = 0; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int before = 0;
		for(int j = 0; j < m; j++) {
			char c; scanf(" %c", &c);
			int now = c=='#';
			qtd += now;
			if(now && before)
				sv[i][j][3] = sv[i][j-1][1] = ++ptr, color[ptr] = 1;
			if(now && last[j])
				sv[i][j][0] = sv[i-1][j][2] = ++ptr;
			before = now;
			last[j] = now;
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			for(int k = 0; k < 4; k++) {
				int x = sv[i][j][k], y = sv[i][j][(k+1)%4], z = sv[i][j][(k+3)%4];
				if(x && y) g[x].pb(y);
				if(x && z) g[x].pb(z);
			}
		}
	}

	printf("%d\n", qtd - (ptr - hk(ptr)));
}