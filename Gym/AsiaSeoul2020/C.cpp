#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

bool on[maxn];
int qtd_filho[maxn];
vector<int> g[maxn], filhos;

int ans = 0;

void pre(int u, int p) {
	qtd_filho[u] = on[u];
	for(int v : g[u])
		if(v != p)
			pre(v, u), qtd_filho[u] += qtd_filho[v];
}

void dfs(int u, int p, bool cima) {
	int cnt = 0;
	for(int v : g[u])
		cnt += qtd_filho[v]>0;
	for(int v : g[u]) {
		if(v != p) {
			qtd_filho[u] -= qtd_filho[v];
			qtd_filho[v] += qtd_filho[u];
			dfs(v, u, cima || on[u]);
			qtd_filho[v] -= qtd_filho[u];
			qtd_filho[u] += qtd_filho[v];
		}
	}
	if(cnt > 1 || on[u]) ++ans;
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1, a, b, trash; i < n; i++)
		scanf("%d %d %d", &a, &b, &trash), g[a].push_back(b), g[b].push_back(a);
	for(int i = 0, a; i < k; i++)
		scanf("%d", &a), on[a] = 1;
	if(k == 1) return puts("1"), 0;
	pre(1, 0);
	dfs(1, 0, 0);
	printf("%d\n", ans);
}