#include <bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define ff first
#define ss second

using pii = pair<int,int>;

constexpr int maxn = 3010, maxq = 1e4+10;

map<pii, int> cost_edge;
map<pii, bool> in_mst;

struct Tree {
	struct DSU {
		int pai[maxn], peso[maxn];
		void init() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
		int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
		bool join(int a, int b) {
			a = find(a), b = find(b);
			if(a == b) return 0;
			if(peso[a] < peso[b]) swap(a, b);
			peso[a] += peso[b];
			pai[b] = a;
			return 1;
		}
	} dsu;

	struct Edge { int x, y, c; bool operator<(Edge o) const { return c < o.c; } };

	vector<Edge> edges;
	vector<int> g[maxn];
	int in[maxn], out[maxn], t, cost_mst;

	void get_mst() {
		sort(all(edges));

		for(Edge e : edges)
			if(dsu.join(e.x, e.y)) cost_mst += e.c, add_edge(e.x, e.y);
	}


	void add_edge(int a, int b) { g[a].push_back(b), g[b].push_back(a); in_mst[pii(a, b)] = in_mst[pii(b, a)] = 1; }

	// lineariza a árvore
	void dfs(int u, int p = -1) {
		in[u] = ++t;
		for(int v : g[u])
			if(v != p) dfs(v, u);
		out[u] = t;
	}

	void init() {
		dsu.init();
		edges.clear();
		for(int i = 0; i < maxn; i++)
			g[i].clear();
		memset(in, 0, sizeof in);
		memset(out, 0, sizeof out);
		t = cost_mst = 0;
	}
} tree;

struct LineSweep {
	struct Ev { int t, x, v; }; // t == 1 -> update com posicao x e valor v, t == 0 -> query do intervalo [posicao_do_sweep, x], com id == v 
	// todas as queries de intervalo [pos, x] tem que vir antes dos updates
	vector<Ev> events[maxn], events_rev[maxn];
	int ans[maxq], n = maxn-5;

	struct SegmentTree {
		int tree[4*maxn];

		void clear() { memset(tree, 0x3f, sizeof tree); } // coloca todo mundo pra infinito porque é uma seg de mínimo

		void upd(int node, int i, int j, int x, int v) {
			if(i == j) return (void)(tree[node] = min(tree[node], v));
			int m = (i+j) >> 1;
			if(x <= m) upd(node<<1, i, m, x, v);
			else upd(node<<1|1, m+1, j, x, v);
			tree[node] = min(tree[node<<1], tree[node<<1|1]);
		}

		int query(int node, int i, int j, int l, int r) {
			if(j < l || i > r) return 0x3f3f3f3f;
			if(i >= l && j <= r) return tree[node];
			int m = (i+j) >> 1;
			return min(query(node<<1, i, m, l, r), query(node<<1|1, m+1, j, l, r));
		}
	} seg;

	// add_query vem ANTES do add_update
	void add_query(int x, int y, int id) { events[x].push_back({0, y, id}); events_rev[y].push_back({0, x, id}); }
	void add_update(int x, int y, int v) { events[x].push_back({1, y, v}); events_rev[y].push_back({1, x, v}); }

	void sweep() {
		seg.clear();

		for(int i = 1; i <= n; i++) {
			for(Ev e : events[i]) {
				int t = e.t, x = e.x, v = e.v;
				if(t == 0) ans[v] = min(ans[v], seg.query(1, 1, n, i, x)); // intervalo [i, x]
				else seg.upd(1, 1, n, x, v);
			}
		}

		seg.clear();

		for(int i = n; i >= 1; i--) {
			for(Ev e : events_rev[i]) {
				int t = e.t, x = e.x, v = e.v;
				if(t == 0) ans[v] = min(ans[v], seg.query(1, 1, n, x, i)); // intervalo [x, i]
				else seg.upd(1, 1, n, x, v);
			}
		}
	}

	void init() {
		memset(ans, 0x3f, sizeof ans);
		for(int i = 0; i < maxn; i++)
			events[i].clear(), events_rev[i].clear();
		n = maxn-5;
	}
} ls;


int main() {
	int n, m; scanf("%d %d", &n, &m);
	while(n) {
		ls.init();
		tree.init();
		cost_edge.clear();
		in_mst.clear();

		for(int i = 0, x, y, c; i < m; i++)
			scanf("%d %d %d", &x, &y, &c), x++, y++, tree.edges.push_back({x, y, c}), cost_edge[pii(x,y)] = cost_edge[pii(y,x)] = c;

		tree.get_mst();
		tree.dfs(1);

		int Q; scanf("%d", &Q);

		long long ANS = 1ll * tree.cost_mst * Q;

		for(int q = 1; q <= Q; q++) {
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c); x++, y++;
			
			ANS -= cost_edge[pii(x, y)];

			if(in_mst[pii(x, y)]) {
				if(tree.in[x] > tree.in[y]) swap(x, y);
				ls.add_query(tree.in[y], tree.out[y], q);
				ls.ans[q] = c; // comentei pra debugar
			} else ls.ans[q] = cost_edge[pii(x, y)];

		}

		for(Tree::Edge e : tree.edges) {
			if(in_mst[pii(e.x, e.y)]) continue;
			int x = e.x, y = e.y, c = e.c;
			if(tree.in[x] > tree.in[y]) swap(x, y);
			ls.add_update(tree.in[x], tree.in[y], c);
		}

		ls.sweep();

		for(int i = 1; i <= Q; i++)
			ANS += ls.ans[i];
		
		printf("%.4lf\n", (double) ((long double)(ANS) / Q));

		scanf("%d %d", &n, &m);
	}
}
