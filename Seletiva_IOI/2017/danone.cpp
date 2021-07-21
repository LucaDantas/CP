// offline
#include <cstdio>
#include <algorithm>
#include <vector>

constexpr int maxn = 2e6+10, inf = 0x3f3f3f3f;

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b]) std::swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
} dsu;

struct Query {
	int l, r, v;
} qry[maxn];

std::vector<int> L[maxn], R[maxn];

bool mark[maxn];
long long val[maxn];

void dfs(int x, long long aq) {
	mark[x] = 1;
	val[x] = aq;
	for(int id : L[x]) {
		auto [l, r, v] = qry[id];
		if(!mark[r]) dfs(r, aq + v);
	}
	for(int id : R[x]) {
		auto [l, r, v] = qry[id];
		if(!mark[l]) dfs(l, aq - v);
	}
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 0; i < q; i++) {
		char c; int l, r, v = -inf; scanf(" %c %d %d", &c, &l, &r);
		if(c == 'L') scanf("%d", &v), L[l].push_back(i), R[r+1].push_back(i);
		qry[i] = {l, r+1, v};
	}
	for(int i = 1; i <= n; i++)
		if(!mark[i]) dfs(i, 0ll);
	for(int i = 0; i < q; i++) {
		auto [l, r, v] = qry[i];
		if(v == -inf) {
			if(dsu.find(l) == dsu.find(r)) printf("%lld\n", val[r] - val[l]);
			else puts("Esquecido");
		} else dsu.join(l, r);
	}
}
