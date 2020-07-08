#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int MAXN = 5e4 + 10;
constexpr int mod = 1000000007;

struct Edge
{
	int u, v, g, s, ind;
} edges[MAXN];

struct DSU {
	int pai[MAXN], peso[MAXN];
	void init(int n) {
		rep(i,1,n+1) pai[i] = i, peso[i] = 1;
	}
	int find(int x) {
		if(pai[x] == x) return x;
		return pai[x] = find(pai[x]);
	}
	void join(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return;

		if(peso[x] < peso[y]) swap(x,y);
		peso[x] += peso[y];
		pai[y] = x;
	}
} dsu;

vector<pii> grafo[MAXN];

int pai[MAXN], edge_pai[MAXN];

void dfs(int u, int p) {
	for(auto nxt : grafo[u]) {
		int v = nxt.ff, id = nxt.ss;
		if(v == p) continue;

		pai[v] = u; edge_pai[v] = id;
		dfs(v,u);
	}
}

Edge get_mx(int v) {
	Edge ans = {-1, -1, -1, -1, -1};

	while(pai[v]) {
		if(ans.s < edges[edge_pai[v]].s)
			ans = edges[edge_pai[v]];
		v = pai[v];
	}

	return ans;
}

int main() {
	int n, m, G, S; scanf("%d %d %d %d", &n, &m, &G, &S);
	int cc = n;
	dsu.init(n);

	rep(i,1,m+1) {
		int u, v, g, s;
		scanf("%d %d %d %d", &u, &v, &g, &s);
		edges[i] = {u, v, g, s, i};
	}

	sort(edges+1, edges+m+1, [](const Edge& a, const Edge& b){
		return a.g < b.g;
	});

	for (int i = 1; i <= m; i++)
		edges[i] = {edges[i].u, edges[i].v, edges[i].g, edges[i].s, i};
	
	vector<Edge> V;
	ll ans = inf;
	int mx = 0;

	rep(i,1,m+1) {
		int u = edges[i].u, v = edges[i].v, g = edges[i].g, s = edges[i].s;
		if(u == v) continue;

		if(dsu.find(u) != dsu.find(v)) {
			V.pb(edges[i]);
			dsu.join(u,v);

			cc--; mx = max(mx, s);
		}
		else {
			rep(k,1,n+1) grafo[k].clear();

			for(auto it : V)
				grafo[it.u].pb({it.v, it.ind}), grafo[it.v].pb({it.u, it.ind});

			pai[u] = 0;
			dfs(u, 0);

			Edge rm = get_mx(v);

			if(s >= rm.s) continue;

			vector<Edge> aux;

			aux.pb(edges[i]), mx = s;
			for(auto E : V)
				if(E.ind != rm.ind)
					aux.pb(E), mx = max(mx, E.s);

			swap(V, aux);
			aux.clear();
		}
		if(cc == 1)
			ans = min(ans, 1ll*G*g + 1ll*S*mx);
	}
	if(ans == inf) ans = -1;
	printf("%lld\n", ans);
}
