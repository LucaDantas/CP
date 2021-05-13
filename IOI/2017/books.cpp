#include "books.h"
#include <cmath>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

constexpr int maxn = 2e6+10;

int t, comp[maxn], dist[maxn], L[maxn], R[maxn], opa[maxn];
std::vector<std::pair<int,int>> g[maxn];

bool foi[maxn];

void bfs(int s) {
	for(int i = 0; i < maxn; i++)
		dist[i] = maxn;
	std::deque<int> q = {s};
	dist[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop_front();
		if(foi[u]) continue;
		foi[u] = 1;
		for(auto pp : g[u]) {
			auto [v, w] = pp;
			if(dist[v] <= dist[u] + w) continue;
			dist[v] = dist[u] + w;
			if(w) q.push_back(v);
			else q.push_front(v);
		}
	}
}

void dfs(int u, const std::vector<int>& p, int& fim) {
	fim = std::max(fim, u);
	comp[u] = t;
	if(!comp[p[u]]) dfs(p[u], p, fim);
}

int pai[maxn], n;
bool mark[maxn];

int pr(int u) { return !mark[u] || u==n-1 ? u : pai[u] = pr(pai[u]); }

long long minimum_walk(std::vector<int> p, int s) {
	n = (int)p.size();
	long long ans = 0;

	std::vector<std::pair<int,int>> seg;

	int tot = 0;
	for(int i = 0; i < n; i++) {
		pai[i] = i+1;
		tot = std::max(tot, p[i]);
		opa[i] = tot>i;
		ans += abs(i-p[i]);
		if(!comp[i] && tot > i) {
			int fim = 0; ++t;
			dfs(i, p, fim);
			seg.push_back({i, fim});
			L[t] = i, R[t] = fim;
		}
	}

	std::sort(seg.begin(), seg.end(), [](std::pair<int,int> x, std::pair<int,int> y) {
		return x.second - x.first < y.second - y.first;
	});

	for(std::pair<int,int> p : seg) {
		auto [l, r] = p;
		for(int i = l; i < r; i = pr(i)) {
			if(L[comp[i]] < l || R[comp[i]] > r)
				g[comp[l]].push_back({comp[i], 0}), g[comp[i]].push_back({comp[l], 0});
			mark[i] = 1;
		}
		mark[l] = mark[r] = 0;
	}

	for(int i = 1; i < n; i++) if(opa[i-1] && comp[i] != comp[i-1])
		g[comp[i]].push_back({comp[i-1], 1}), g[comp[i-1]].push_back({comp[i], 1});


	if(comp[s]) {
		bfs(comp[s]);
		for(int i = 1; i <= t; i++)
			if(dist[i] < maxn) { ans += dist[i]<<1; break; }
	}

	int cnt = 0;
	for(int i = s-1; i >= 0; i--)
		if(!opa[i]) ++cnt;
		else ans += cnt<<1, cnt = 0;

	cnt = 0;
	for(int i = s; i < n; i++)
		if(!opa[i]) ++cnt;
		else ans += cnt<<1, cnt = 0;

	return ans;
}
