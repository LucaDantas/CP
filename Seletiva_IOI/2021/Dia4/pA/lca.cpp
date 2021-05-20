int pai[maxn][logn], depth[maxn], n;

void dfs(int u) {
	for(int v : g[u]) {
		if(v == pai[u][0]) continue;
		depth[v] = depth[u] + 1;
		pai[v][0] = u;
		dfs(v);
	}
}

void build() {
	for(int l = 1; l < logn; l++)
		for(int i = 1; i <= n; i++)
			pai[i][l] = pai[pai[i][l-1]][l-1];
}

int lca(int a, int b) {
	if(depth[a] < depth[b])
		swap(a, b);
	for(int l = logn-1; l >= 0; l--)
		if(depth[a] - (1 << l) >= depth[b])
			a = pai[a][l];
	if(a == b) return a;
	for(int l = logn-1; l >= 0; l--)
		if(pai[a][l] != pai[b][l]) a = pai[a][l], b = pai[b][l];
	return pai[a][0];
}

int dist(int a, int b) {
	return depth[a] + depth[b] - 2*depth[lca(a, b)];
}
