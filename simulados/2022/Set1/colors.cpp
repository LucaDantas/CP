#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct DSU {
	int pai[maxn], peso[maxn], t;
	struct SV { int a, b, peso_a, peso_b; };
	
	vector<SV> sv;

	/* void init(int n) {
		for(int i = 0; i <= n; i++)
			pai[i] = i, peso[i] = 1;
		sv.clear();
		t = 0;
	} */
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	
	int find(int x) { return pai[x] == x ? x : find(pai[x]); }

	void join(int a, int b) {
		a = find(a), b = find(b);

		if(peso[a] < peso[b])
			swap(a, b);
		
		++t;
		sv.push_back({a, b, peso[a], peso[b]});

		if(a == b) return;

		pai[b] = a;
		peso[a] += peso[b];
	}
	void rollback(int voltar) {
		while(t > voltar) {
			--t;
			auto [a, b, peso_a, peso_b] = sv.back();
			sv.pop_back();
			pai[a] = a, pai[b] = b;
			peso[a] = peso_a, peso[b] = peso_b;
		}
	}
} dsu;

int a[maxn], b[maxn];

vector<int> posA[maxn], posB[maxn];

int ans = 1;

struct SegmentTree {
	vector<pair<int,int>> tree[4*maxn];
	void addEdge(int node, int i, int j, int l, int r, pair<int,int> e) {
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(tree[node].push_back(e));
		int m = (i+j) >> 1;
		addEdge(node<<1, i, m, l, r, e);
		addEdge(node<<1|1, m+1, j, l, r, e);
	}
	void go(int node, int i, int j) {
		int voltar = dsu.t;
		for(auto e : tree[node])
			dsu.join(e.first, e.second);

		if(i == j) {
			vector<int> ids;
			for(int x : posA[i]) // salvo as componentes no grafo atual de cada um dos caras que tem a[i] == query atual
				ids.push_back(dsu.find(x));
			sort(ids.begin(), ids.end());

			for(int x : posB[i])
				ans &= binary_search(ids.begin(), ids.end(), dsu.find(x));

			dsu.rollback(voltar);
			return;
		}

		int m = (i+j) >> 1;
		go(node<<1, i, m); // ele da roolback sozinho pra voltar como recebeu
		go(node<<1|1, m+1, j);

		dsu.rollback(voltar);
	}
} seg;

void clean(int n, int m) {
	dsu.rollback(0);

	for(int i = 1; i <= n; i++)
		posA[i].clear(), posB[i].clear(), a[i] = 0, b[i] = 0;

	ans = 1;

	for(int i = 1; i <= 4*n; i++)
		seg.tree[i].clear();
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			scanf("%d", a+i), posA[a[i]].push_back(i);
		for(int i = 1; i <= n; i++)
			scanf("%d", b+i), posB[b[i]].push_back(i);

		bool ruim = 0;
		for(int i = 1; i <= n; i++)
			if(a[i] < b[i]) { ruim = 1; }

		for(int i = 0; i < m; i++) {
			int x, y; scanf("%d %d", &x, &y);
			
			if(b[x] > b[y])
				swap(x, y);

			if(!ruim && a[x] >= b[y])
				seg.addEdge(1, 1, n, b[y], min(a[x], a[y]), {x, y});
		}

		if(ruim) { puts("0"); clean(n, m); continue; }

		seg.go(1, 1, n);

		printf("%d\n", ans);

		clean(n, m);
	}
}
