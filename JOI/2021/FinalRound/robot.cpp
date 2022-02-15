#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct Edge { int a, b, c, p; } edges[maxn];

vector<pair<int,int>> g[maxn];

map<pair<int,int>, long long> dp;
set<pair<int,int>> mark;

map<int, vector<pair<int,int>>> viz[maxn];
map<int,long long> soma[maxn];

priority_queue<pair<long long,pair<int,int>>> q;

inline void add(const pair<int,int>& p, long long val) { if(!dp.count(p) || val < dp[p]) dp[p] = val, q.push({-val, p}); }

void dijkstra() {
	dp[{1,0}] = 0;

	// dp[index][cor]
	q.push({0, {1,0}});

	while(q.size()) {
		auto [u, cor] = q.top().second;
		long long val = -q.top().first; q.pop();

		if(mark.count({u, cor})) continue;
		mark.insert({u, cor});

		if(!cor) {
			for(auto [v, id] : g[u]) {
				int c = edges[id].c, p = edges[id].p;
				add({v, c}, val);
				add({v, 0}, min(val + soma[u][c] - p, val + p));
			}
		} else {
			vector<pair<int,int>>& adj = viz[u][cor];
			for(auto [v, p] : adj)
				add({v, 0}, val + soma[u][cor] - p);
		}
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b, c, p; i < m; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &p), edges[i] = {a, b, c, p};
		g[a].push_back({b, i}), g[b].push_back({a, i});
		viz[a][c].push_back({b, p});
		viz[b][c].push_back({a, p});
		soma[a][c] += p;
		soma[b][c] += p;
	}
	dijkstra();
	printf("%lld\n", dp.count({n, 0}) ? dp[{n, 0}] : -1);
}
