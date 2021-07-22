#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5 + 10;

vector<int> g[maxn];

bool mark[maxn];
int sz[maxn];

void pre(int u) {
	sz[u] = 1; mark[u] = 1;
	for(int v : g[u]) if(!mark[v])
		pre(v), sz[u] += sz[v];
}

vector<int> mae, f1, f2;

void get(int u, vector<int>& ad) {
	ad.pb(u); mark[u] = 1;
	for(int v : g[u]) if(!mark[v])
		get(v, ad);
}

void dfs(int u, int colocar) {
	mae.pb(u); mark[u] = 1;
	for(int v : g[u]) if(!mark[v]) {
		if(!colocar) get(v, f2);
		else if((sz[v]<<1) < colocar) colocar -= sz[v]<<1, get(v, f1);
		else {
			if((sz[v]<<1) == colocar) get(v, f1);
			else dfs(v, colocar - 1);
			colocar = 0;
		}
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	pre(1); memset(mark, 0, sizeof mark);
	dfs(1, n-1);
	printf("%ld %d\n", mae.size(), (n-(int)mae.size()) >> 1);
	for(int x : mae)
		printf("%d ", x);
	puts("");
	for(int x : f1)
		printf("%d ", x);
	puts("");
	for(int x : f2)
		printf("%d ", x);
	puts("");
}

