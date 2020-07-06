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

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

struct Edge {
	int u, v, w, ind, done;
};

int fam[MAXN], peso[MAXN], pai[MAXN][LOGN+1], maior[MAXN][LOGN+1], level[MAXN];

vector<pii> g[MAXN];

void init(int n) {
	rep(i,1,n+1) fam[i] = i, peso[i] = 1;
}

int find(int x) {
	if(x == fam[x]) return x;
	return fam[x] = find(fam[x]);
}

void join(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) swap(x,y);
	fam[y] = x;
	peso[x] += peso[y];
}

void dfs(int u, int p = -1) {
	for(auto nxt : g[u]) {
		int v = nxt.ff, w = nxt.ss;
		if(v == p) continue;
		pai[v][0] = u;
		maior[v][0] = w;
		level[v] = level[u] + 1;
		dfs(v, u);
	}
}

ll soma = 0;

int biggest_path(int x, int y) {
	int ans = 0;
	if(level[x] < level[y]) swap(x,y);
	dec(i, LOGN-1, 0) if(level[x] - (1<<i)  >= level[y]) {
		ans = max(ans, maior[x][i]);
		x = pai[x][i];
	}
	if(x == y) return ans;
	dec(i, LOGN-1, 0) if(pai[x][i] != pai[y][i]) {
		ans = max({ans, maior[x][i], maior[y][i]});
		x = pai[x][i];
		y = pai[y][i];
	}
	ans = max({ans, maior[x][0], maior[y][0]});
	x = pai[x][0], y = pai[y][0];
	return ans;
}

ll ans[MAXN];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	init(n);
	vector<Edge> edges;

	rep(i,0,m) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		edges.pb({u,v,w,i,0});
	}
	
	sort(all(edges),[](const Edge& a, const Edge& b){return a.w < b.w;});
	rep(i,0,m) {
		int u = edges[i].u;
		int v = edges[i].v;
		int w = edges[i].w;
		if(find(u) == find(v)) continue;
		edges[i].done = 1;
		soma += w;
		g[u].pb({v,w});
		g[v].pb({u,w});
		join(u, v);
	}
	
	// we have our mst, so we'll do the binary lifting and then compute the answer
	level[1] = 1;
	dfs(1);
	for(int j = 1; j < LOGN; j++) {
		for(int i = 1; i <= n; i++) {
			pai[i][j] = pai[pai[i][j-1]][j-1];
			maior[i][j] = max(maior[i][j-1],maior[pai[i][j-1]][j-1]);
		}
	}

	rep(i,0,m) {
		int u = edges[i].u;
		int v = edges[i].v;
		int w = edges[i].w;
		if(edges[i].done) ans[edges[i].ind] = soma;
		else {
			int remover = biggest_path(u, v);
			ans[edges[i].ind] = soma + w - remover;
		}
	}

	rep(i,0,m) printf("%lld\n", ans[i]);
}
