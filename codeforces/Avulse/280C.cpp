#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e5+10;

vector<int> g[maxn];

double ans;

void dfs(int u, int depth, int p) {
	ans += 1.00/(double)(depth);
	for(int v : g[u])
		if(v != p)
			dfs(v, depth+1, u);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	dfs(1, 1, 0);
	printf("%.6lf\n", ans);
}