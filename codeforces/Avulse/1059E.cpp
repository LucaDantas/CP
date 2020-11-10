#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define pb push_back

constexpr int maxn = 1e5+10, logn = 20;

int p[maxn][logn], go[maxn], ans;
ll w[maxn][logn];
vector<int> g[maxn];

int dfs(int u) {
	int menor = maxn;
	for(int v : g[u])
		menor = min(menor, dfs(v));
	if(menor <= u)
		return menor;
	ans++;
	return go[u];
}

int main() {
	int n, L; ll s; scanf("%d %d %lld", &n, &L, &s);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &w[i][0]);
		if(w[i][0] > s) {
			puts("-1");
			return 0;
		}
	}
	for(int i = 2; i <= n; i++)
		scanf("%d", &p[i][0]), g[p[i][0]].pb(i);
	for(int l = 1; l < logn; l++) {
		for(int i = 1; i <= n; i++) {
			p[i][l] = p[p[i][l-1]][l-1];
			w[i][l] = w[i][l-1] + w[p[i][l-1]][l-1];
		}
	}
	for(int i = 1; i <= n; i++) {
		int now = i, tam = 1; ll peso = 0;
		for(int l = logn-1; l >= 0; l--) {
			if(!p[now][l] || tam + (1 << l) > L) continue;
			if(peso + w[now][l] + w[p[now][l]][0] <= s)
				peso += w[now][l], now = p[now][l], tam += (1 << l);
		}
		go[i] = now;
	}
	dfs(1);
	printf("%d\n", ans);
}