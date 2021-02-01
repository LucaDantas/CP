#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())

constexpr int maxn = 2e5+10;

int tam[maxn];
vector<pair<int,int>> g[maxn];
bool mark[maxn];

queue<int> q;

vector<int> ans;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &tam[i]);
	for(int i = 1; i <= m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb({b, i}); g[b].pb({a, i});
	}
	for(int i = 1; i <= n; i++)
		if(sz(g[i]) <= tam[i]) q.push(i);
	int qtd = 0;
	while(q.size()) {
		++qtd;
		int u = q.front(); q.pop();
		for(auto pp : g[u]) {
			auto [v, i] = pp;
			if(!mark[i]) ans.pb(i), mark[i] = 1;
			if(++tam[v] == sz(g[v]))
				q.push(v);
		}
	}
	puts(qtd==n?"ALIVE":"DEAD");
	if(qtd==n) {
		reverse(ans.begin(), ans.end());
		for(int x : ans) printf("%d ", x);
		printf("\n");
	}
}