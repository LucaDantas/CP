#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 4e5+10;

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
} dsu;

map<int,int> qtd;

struct Itv { int l, r; bool operator<(const Itv& o) { return r-l > o.r-o.l; } };
vector<Itv> itv;

int pai[maxn];
bool vis[maxn];

long long plan_roller_coaster(vector<int> s, vector<int> t) {
	int n = (int) s.size();
	long long ans = 0;
	
	for(int i = 0; i < n; i++) {
		qtd[s[i]]++, qtd[t[i]]--;
		itv.push_back({min(s[i], t[i]), max(s[i], t[i])});
	}

	for(auto it = qtd.begin(); it != qtd.end(); ++it) {
		if(it != qtd.begin())
			it->second += prev(it)->second;

		if(it->second != 1 && next(it) != qtd.end()) {
			itv.push_back({it->first, next(it)->first});
			if(it->second > 1)
				ans += 1ll * (it->second-1) * (next(it)->first - it->first);
		}
	}

	// agora que eu tenho todos os intervalos, tenho que checar as intersecções
	
	sort(itv.begin(), itv.end()); // ordeno pelo de maior tamanho

	int coord = 0;
	for(auto& it : qtd)
		it.second = ++coord;

	iota(pai+1, pai+coord+1, 1); // todo mundo começa apontando pro próximo
	
	for(auto [l, r] : itv) {
		l = qtd[l], r = qtd[r];
		vis[l] = 1, vis[r] = 1;
		while(l < r) {
			if(vis[l])
				dsu.join(l, r);
			int nxt = pai[l];
			pai[l] = r;
			l = nxt;
		}
	}

	vector<array<int,3>> edges;
	vector<int> points;

	for(auto [l, r] : itv)
		points.push_back(l), points.push_back(r);
	sort(points.begin(), points.end());
	
	for(int i = 1; i < points.size(); i++) {
		int eu = dsu.find(qtd[points[i]]), ant = dsu.find(qtd[points[i-1]]);
		if(eu != ans)
			edges.push_back({points[i] - points[i-1], eu, ant});
	}

	sort(edges.begin(), edges.end());
	for(auto [sz, x, y] : edges)
		if(dsu.find(x) != dsu.find(y))
			ans += sz, dsu.join(x, y);
	
	return ans;
}
