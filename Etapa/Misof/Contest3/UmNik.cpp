#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, _VA_ARGS_);fflush(stderr);
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const int INF = (int)2e9 + 77;
const int N = 1 << 19;
const int M = 300300;
pair<int, pii> ed[M];
bool inMst[M];
int n, m;
vector<pii> g[M];
int par[M];
int sz[M];
int highest[M];
int w[M];
bool act[M];
int t[M][2];
int T;
int h[M];
int pp[M];

int getPar(int v) {
	return par[v] == v ? v : par[v] = getPar(par[v]);
}
bool unite(int v, int u) {
	v = getPar(v);
	u = getPar(u);
	if (v == u) return false;
	if (sz[v] < sz[u]) swap(v, u);
	sz[v] += sz[u];
	par[u] = v;
	if (h[highest[u]] < h[highest[v]]) highest[v] = highest[u];
	w[v] = min(w[v], w[u]);
	return true;
}

void read() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int v, u, c;
		scanf("%d%d%d", &v, &u, &c);
		v--;u--;
		ed[i] = mp(c, mp(v, u));
	}
	sort(ed, ed + m);
	for (int v = 0; v < n; v++) {
		par[v] = v;
		sz[v] = 1;
	}
	for (int i = 0; i < m; i++) {
		int v = ed[i].second.first, u = ed[i].second.second;
		if (unite(v, u)) {
			eprintf("inMst %d %d %d\n", v, u, ed[i].first);
			inMst[i] = true;
			g[v].push_back(mp(u, ed[i].first));
			g[u].push_back(mp(v, ed[i].first));
		}
	}
}

struct Node {
	int l, r, val;

	Node() : l(), r(), val(INF) {}
	Node(int _l, int _r) : l(_l), r(_r), val(INF) {}

	void applyMin(int x) {
		val = min(val, x);
	}
};
Node tree[2][2 * N + 5];

void build() {
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < N; i++)
			tree[k][N + i] = Node(i, i + 1);
		for (int i = N - 1; i > 0; i--)
			tree[k][i] = Node(tree[k][2 * i].l, tree[k][2 * i + 1].r);
	}
}
void push(int k, int v) {
	assert(v < N);
	for (int u = 2 * v; u < 2 * v + 2; u++) {
		tree[k][u].applyMin(tree[k][v].val);
	}
	tree[k][v].val = INF;
}

void applyMin(int k, int v, int l, int r, int x) {
	if (l <= tree[k][v].l && tree[k][v].r <= r) {
		tree[k][v].applyMin(x);
		return;
	}
	if (l >= tree[k][v].r || tree[k][v].l >= r) return;
	push(k, v);
	for (int u = 2 * v; u < 2 * v + 2; u++)
		applyMin(k, u, l, r, x);
}
int getVal(int k, int v, int p) {
	if (v >= N) return tree[k][v].val;
	push(k, v);
	if (p < tree[k][2 * v].r)
		return getVal(k, 2 * v, p);
	else
		return getVal(k, 2 * v + 1, p);
}
void setPoint(int k, int v, int x) {
	getVal(k, 1, v);
	tree[k][N + v].val = x;
}

void dfs(int v, int par) {
	t[v][0] = T++;
	for (pii e : g[v]) {
		int u = e.first;
		if (u == par) continue;
		h[u] = h[v] + 1;
		pp[u] = v;
		w[u] = e.second;
		dfs(u, v);
	}
	t[v][1] = T;
}

void dfsActivate(int v, int c) {
	eprintf("activate %d %d\n", v, c);
	assert(!act[v]);
	act[v] = 1;
	eprintf("val = %d\n", getVal(0, 1, t[v][0]));
	setPoint(1, t[v][0], c + getVal(0, 1, t[v][0]));
	for (pii e : g[v]) {
		if (e.second > c) continue;
		int u = e.first;
		if (h[u] < h[v]) continue;
		dfsActivate(u, c);
	}
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	read();
	dfs(0, -1);
	for (int v = 0; v < n; v++)
		eprintf("%d : %d %d\n", v, t[v][0], t[v][1]);
	build();
	for (int v = 0; v < n; v++) {
		par[v] = v;
		sz[v] = 1;
		highest[v] = v;
	}
	w[0] = INF;
	act[0] = 1;
	for (int i = 0; i < m; i++) {
		int v = ed[i].second.first, u = ed[i].second.second;
		int c = ed[i].first;
		if (h[v] > h[u]) swap(v, u);
		eprintf("work %d %d %d\n", v, u, c);
		if (inMst[i]) {
			applyMin(0, 1, t[u][0], t[u][1], c);
			if (!act[v] || act[u]) continue;
			dfsActivate(u, c);
		} else {
			while(true) {
				v = highest[getPar(v)];
				u = highest[getPar(u)];
				if (v == u) break;
				if (h[v] > h[u]) swap(v, u);
				assert(unite(u, pp[u]));
			}
			v = getPar(v);
			int cc = w[v];
			v = highest[v];
			applyMin(0, 1, t[v][0], t[v][1], cc);
			eprintf("ansOnSegm %d %d %d\n", t[v][0], t[v][1], c + cc);
			applyMin(1, 1, t[v][0], t[v][1], c + cc);
		}
	}
	for (int v = 1; v < n; v++)
		printf("%d\n", getVal(1, 1, t[v][0]));

	return 0;
}
