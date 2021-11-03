#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

std::vector<int> g[maxn], ini[maxn], fim[maxn];

int U[maxn], V[maxn], c[maxn];
long long ans;

bool ok = 1;

struct ST {
	long long lazy;
	map<int,long long> mp;
	multiset<long long> valores;

	ST() { lazy = 0; }
	
	void add(long long v) { lazy += v; }
	void insert(int id, long long custo) { mp[id] = custo; valores.insert(custo); }
	long long get() { if(!valores.size()) return ok=0; return (*valores.begin()) + lazy; }
	int sz() { return (int)valores.size(); }
	void erase(int id) { valores.erase(valores.find(mp[id])); mp.erase(id); }
};

void merge(ST *&a, ST *&b) {
	if(a->sz() < b->sz()) {
		for(auto it : a->mp)
			b->insert(it.first, it.second + a->lazy - b->lazy);
		swap(a, b);
	} else {
		for(auto it : b->mp)
			a->insert(it.first, it.second + b->lazy - a->lazy);
	}
}

ST *atv[maxn];

void dfs(int u, int p) {
	atv[u] = new ST;

	long long aq = 0;
	for(int v : g[u])
		if(v != p) dfs(v, u), aq += atv[v]->get();

	for(int id : ini[u])
		atv[u]->insert(id, aq + c[id]);

	for(int v : g[u]) if(v != p) {
		atv[v]->add(aq - atv[v]->get());
		merge(atv[u], atv[v]);
	}

	if(u == 1) ans = atv[u]->get();

	for(int id : fim[u])
		atv[u]->erase(id);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	if(n == 1) return puts("0"), 0;
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	for(int i = 0; i < m; i++)
		scanf("%d %d %d", U+i, V+i, c+i), ini[U[i]].push_back(i), fim[V[i]].push_back(i);

	dfs(1, 0);

	printf("%lld\n", ok ? ans : -1);
}
