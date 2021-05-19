// Centroid
// Em cada nivel do centroid vou tanto da esq pra dir como o contrario
// Faço um hld q salva pra cada folha qual a menor profundidade na subarvore - profundidade real minha *2
// Em cada query como ta no centroid o valor é profundidade modificada de cada cara com o centroid junto com
// o real na segunda arvore + menor query em todos os meus pais, faco a query no hld
// Quando terminar uma subarvore atualizo o valor dele e de todos os pais no hld com a profundidade real + 
// profundidade na arvore do centroid
// Seg de color update e tá safe

// Versao com HLD q dá tle. Eu vou deixar pq ficou bem bonito mesmo q esteja mais lento

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int maxn = 250010;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct SegmentTree
{
	struct Node
	{
		long long mx_a, mn_a, mn_b, ans, lazy_a;
		Node(long long val = inf) : mx_a(inf), mn_a(inf), mn_b(val), ans(inf), lazy_a(inf) {}
		void merge(const Node& a, const Node& b) {
			mx_a = max(a.mx_a, b.mx_a);
			mn_a = min(a.mn_a, b.mn_a);
			mn_b = min(a.mn_b, b.mn_b);
			ans = min(a.ans, b.ans);
		}
	} tree[1<<20];

	void flush(int node, int i, int j) {
		if(tree[node].lazy_a == inf) return;
		
		if(i != j) {
			tree[node<<1].lazy_a = tree[node].lazy_a;
			tree[node<<1|1].lazy_a = tree[node].lazy_a;
		}

		tree[node].mn_a = tree[node].mx_a = tree[node].lazy_a;

		tree[node].ans = tree[node].mn_b + tree[node].lazy_a;
		tree[node].lazy_a = inf;
	}

	void build(int node, int i, int j, const long long* b) {
		if(i == j) return (void)(tree[node] = Node(-2*b[i]));
		int m = (i+j) >> 1;
		build(node<<1, i, m, b); build(node<<1|1, m+1, j, b);
		tree[node].merge(tree[node<<1], tree[node<<1|1]);
	}

	void upd(int node, int i, int j, int l, int r, long long val) {
		flush(node, i, j);
		if(tree[node].mx_a <= val || i > r || j < l) return;
		if(i >= l && j <= r && tree[node].mx_a == tree[node].mn_a) {
			tree[node].lazy_a = val;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, val);
		upd(node<<1|1, m+1, j, l, r, val);
		tree[node].merge(tree[node<<1], tree[node<<1|1]);
	}

	long long query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l) return inf;
		if(i >= l && j <= r) return tree[node].ans;
		int m = (i+j) >> 1;
		return min(query(node<<1, i, m, l, r), query(node<<1|1, m+1, j, l, r));
	}

	void clear() { tree[1].lazy_a = inf-1; flush(1, 1, 2); }
};

struct HLD
{
	vector<pii> g[maxn];
	int in[maxn], out[maxn], chain[maxn], sz[maxn], pai[maxn], t, n;
	long long depth[maxn], depth_linear[maxn];
	SegmentTree seg;

	void pre(int u) {
		sz[u] = 1;
		for(pii& pp : g[u]) {
			auto [v, w] = pp;
			
			depth[v] = depth[u] + w;
			g[v].erase(find(g[v].begin(), g[v].end(), pii(u, w)));

			pai[v] = u;
			pre(v);
			
			sz[u] += sz[v];
			if(sz[v] > sz[g[u][0].first])
				std::swap(pp, g[u][0]);
		}
	}

	void dfs(int u) {
		in[u] = ++t;
		for(auto [v, w] : g[u]) {
			chain[v] = (v == g[u][0].first) ? chain[u] : v;
			dfs(v);
		}
		out[u] = t;
	}

	void init(int _n) {
		n = _n;
		chain[1] = 1; pai[1] = -1;
		pre(1); dfs(1);
		for(int i = 1; i <= n; i++)
			depth_linear[in[i]] = depth[i];
		seg.build(1, 1, n, depth_linear);
	}

	void upd(int u, long long val) {
		for(; u != -1; u = pai[chain[u]])
			seg.upd(1, 1, n, in[chain[u]], in[u], val);
	}

	long long query(int u) {
		long long ans = inf;
		for(; u != -1; u = pai[chain[u]])
			ans = min(ans, seg.query(1, 1, n, in[chain[u]], in[u]));
		return ans;
	}

	void clear() { seg.clear(); }
} hld;

vector<pii> g[maxn]; // tree 1, tree 2 is the on in the hld

long long ans[maxn];

struct Centroid
{
	int sz[maxn]; bool mark[maxn];
	long long depth[maxn];
	void dfs(int u, int p) {
		sz[u] = 1;
		for(auto [v, w] : g[u]) {
			if(mark[v] || v == p) continue;
			dfs(v, u); sz[u] += sz[v];
		}
	}
	int get(int u) {
		for(auto [v, w] : g[u]) if(!mark[v] && (sz[v]<<1) > sz[u])
			return (sz[u]-=sz[v], sz[v]+=sz[u], get(v));
		return u;
	}
	void calc(int u, int p, vector<int>& vis) {
		vis.push_back(u);
		for(auto [v, w] : g[u]) if(!mark[v] && v != p)
			depth[v] = depth[u] + w, calc(v, u, vis);
	}
	void decompose(int u) {
		dfs(u, 0);
		u = get(u); mark[u] = 1;
		static vector<int> vis; vis.clear();
		depth[u] = 0; calc(u, 0, vis);
		
		for(int x : vis) {
			ans[x] = min(ans[x], depth[x] + hld.depth[x] + hld.query(x));
			hld.upd(x, hld.depth[x] + depth[x]);
		}
		hld.clear();

		reverse(vis.begin(), vis.end());
		for(int x : vis) {
			ans[x] = min(ans[x], depth[x] + hld.depth[x] + hld.query(x));
			hld.upd(x, hld.depth[x] + depth[x]);
		}
		hld.clear();

		for(auto [v, w] : g[u]) if(!mark[v])
			decompose(v);
	}
} centroid;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].push_back(pii(b, w));
		g[b].push_back(pii(a, w));
	}
	for(int i = 1; i < n; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		hld.g[a].push_back(pii(b, w));
		hld.g[b].push_back(pii(a, w));
	}

	hld.init(n);

	memset(ans, 0x3f, sizeof ans);

	centroid.decompose(1);

	for(int i = 1; i <= n; i++)
		printf("%lld%c", ans[i], " \n"[i==n]);
}
