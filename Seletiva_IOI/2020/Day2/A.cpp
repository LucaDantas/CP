#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define ff first
#define ss second

constexpr int maxn = 1e5+10;

int a[maxn], sz[maxn];

vector<pii> g[maxn];

priority_queue<int> q;

void dfs(int u, int p) {
	sz[u] = a[u];
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss;
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
		if(!sz[v]) q.push(-w);
	}
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1, a, b, w; i < n; i++)
		scanf("%d %d %d", &a, &b, &w), g[a].pb({b, w}), g[b].pb({a, w});
	dfs(1, 0);
	int ans = 0;
	if(k > (int)q.size() || sz[1]) {puts("-1"); return 0;}
	while(k--)
		ans -= q.top(), q.pop();
	printf("%d\n", ans);
}