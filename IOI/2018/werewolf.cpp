#include "werewolf.h"
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using pii = pair<int,int>;

#define all(a) (a).begin(), (a).end()
#define pb push_back
#define ff first
#define ss second

constexpr int maxn = 2e6+10, logn = 22;

int n;

struct DSU
{
	int pai[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i; }
	void init() { for(int i = 0; i < maxn; i++) pai[i] = i; }
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		pai[b] = a;
		return 1;
	}
} dsu;

struct KRT
{
	vector<int> g[maxn]; // graph pointing down
	int tab[maxn][logn], val[maxn], head = 0, t = 1;

	int in[maxn], out[maxn];

	DSU aux;

	void addEdge(int from, int to, int weight) {
		head = from;
		val[from] = weight;

		to = aux.find(to); // gets the head of the component
		aux.join(from, to); // make him my son

		tab[to][0] = from;
		g[from].pb(to);
	}

	void dfs(int u) {
		if(u <= n) return (void)(in[u] = out[u] = t++);

		in[u] = t;
		for(int v : g[u])
			dfs(v);
		out[u] = t-1;
	}

	void build() {
		dfs(head);

		for(int l = 1; l < logn; l++)
			for(int i = 1; i <= head; i++)
				tab[i][l] = tab[tab[i][l-1]][l-1];
	}

	int get(int u, int v, int k) {
		auto comp = [&](int a, int b) { return k?a>=b:a<=b; };
		for(int l = logn-1; l >= 0; l--) {
			if(tab[u][l] && comp(val[tab[u][l]], v))
				u = tab[u][l];
		}
		return u;
	}
} krt[2];

struct Event
{
	int t, x, y1, y2, id;
	bool operator<(Event e) {
		if(x == e.x) return t < e.t;
		return x < e.x;
	}
} events[maxn];

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
	int get(int l, int r) { return query(r) - query(l-1); }
} bit;

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
	vector<int> S, vector<int> E, vector<int> L, vector<int> R) {

	n = N;

	vector<pii> edges;
	int M = (int)X.size();
	for(int i = 0; i < M; i++) {
		if(X[i] > Y[i]) swap(X[i], Y[i]);
		++X[i], ++Y[i];

		edges.pb({X[i], Y[i]});
	}


	{
		sort(all(edges), [](pii a, pii b) {
			return a.first > b.first;
		});

		int cnt = N;
		for(int i = 0; i < M; i++) {
			int a = edges[i].ff, b = edges[i].ss;
			if(dsu.join(a, b)) {
				++cnt;
				krt[0].addEdge(cnt, a, a); // from, to, value of new node
				krt[0].addEdge(cnt, b, a);
			}
		}

		krt[0].build();
	}

	{
		dsu.init();

		// Sort by increasing big value
		sort(all(edges), [](pii a, pii b) {
			return a.ss < b.ss;
		});

		int cnt = N;
		for(int i = 0; i < M; i++) {
			int a = edges[i].ff, b = edges[i].ss;
			if(dsu.join(a, b)) {
				++cnt;
				krt[1].addEdge(cnt, a, b);
				krt[1].addEdge(cnt, b, b);
			}
		}

		krt[1].build();
	}

	int Q = S.size();

	vector<int> ans(Q);

	for(int i = 1; i <= N; i++)
		events[i] = {0, krt[0].in[i], krt[1].in[i], -1, -1};

	for(int i = 0; i < Q; i++) {
		if(S[i] < L[i] || E[i] > R[i]) ans[i] = -2*maxn;

		++S[i], ++E[i], ++L[i], ++R[i];

		int p1 = krt[0].get(S[i], L[i], 1);
		int p2 = krt[1].get(E[i], R[i], 0);

		events[N+2*i+1] = {-1, krt[0].in[p1], krt[1].in[p2], krt[1].out[p2], i},
		events[N+2*i+2] = {1, krt[0].out[p1], krt[1].in[p2], krt[1].out[p2], i};
	}

	sort(events+1, events+N+2*Q+1);

	for(int i = 1; i <= N+2*Q; i++) {
		Event e = events[i];
		if(e.t == 0) bit.upd(e.y1, 1);
		else ans[e.id] += e.t * bit.get(e.y1, e.y2);
	}

	for(int i = 0; i < Q; i++)
		ans[i] = ans[i]>0;
	return ans;
}
