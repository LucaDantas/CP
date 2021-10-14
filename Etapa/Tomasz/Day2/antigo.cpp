#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

pair<int,int> pai[maxn];

vector<pair<int,int>> g[maxn];

void dfs(int u, int p = 0) {
	for(auto pp : g[u]) {
		int v = pp.first, id = pp.second;
		if(v != p) dfs(v, u), pai[v] = {u, id};
	}
}

struct Edge {
	int a, b, c;
} edges[maxn];

int cnt[maxn], ans;

vector<int> cores;

void get(int u) {
	while(u != 1) {
		cores.pb(edges[pai[u].second].c);
		u = pai[u].first;
	}
	ans = 0;
	for(int x : cores)
		if(!cnt[x]) ++ans, cnt[x] = 1;
	for(int x : cores)
		cnt[x] = 0;
	cores.clear();
}

int main() {
	int n, m, q; scanf("%d %d %d", &n, &m, &q);
	for(int i = 1, a, b, c; i < n; i++)
		scanf("%d %d %d", &a, &b, &c), g[a].pb({b, i}), g[b].pb({a, i}), edges[i] = {a, b, c};
	dfs(1);

	while(q--) {
		char c; scanf(" %c", &c);
		if(c == 'Z') {
			int u; scanf("%d", &u);
			get(u);
			printf("%d\n", ans);
		} else {
			int i, val; scanf("%d %d", &i, &val);
			edges[i].c = val;
		}
	}
}