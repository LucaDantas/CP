#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define clr(a, b) memset(a, b, sizeof a)

constexpr int maxn = 110, maxn2 = maxn*maxn;

int a[maxn][maxn], rot;

int val(char r) {
	return r=='^'?0:r=='>'?1:r=='v'?2:3;
}

vector<int> g[maxn2];

bool mark[maxn2], match[maxn2];
int edge_match[maxn2], color[maxn2];

int dfs(int u) {
	mark[u] = 1;
	if(color[u]) {
		if(match[u]) {
			int ans = dfs(edge_match[u]);
			if(!ans) return 0;
			return 1;
		}
		match[u] = 1;
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v]) continue;
		int ans = dfs(v);
		if(!ans) continue;
		match[u] = 1;
		edge_match[u] = v;
		edge_match[v] = u;
		return 1;
	}

	return 0;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			char c, r; scanf(" %c%c", &c, &r);
			a[i][j] = c=='R'; // L -> 0, R -> 1
			color[i*m+j] = a[i][j];
			rot += val(r);
			if(rot >= 4) rot -= 4;
			if(i && a[i-1][j] != a[i][j]) {
				g[i*m+j].pb((i-1)*m+j);
				g[(i-1)*m+j].pb(i*m+j);
			}
			if(j && a[i][j-1] != a[i][j]) {
				g[i*m+j].pb(i*m+j-1);
				g[i*m+j-1].pb(i*m+j);
			}
		}
	}

	int ans = 0;
	for(int i = 0; i < n*m; i++) {
		if(color[i] || match[i]) continue;
		clr(mark, 0);
		ans += dfs(i);
	}

	bool ok = 0;
	int rot_aq = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(!match[i*m+j]) { ok = 1; break; }
			if(color[i*m+j]) continue;
			int y = edge_match[i*m+j]%m;
			if(y == j) rot_aq += 2, rot_aq %= 4;
		}
		if(ok) break;
	}

	if(rot_aq == rot) ok = 1;

	printf("%d\n", min(ans, n*m/2-(1-ok)));
}