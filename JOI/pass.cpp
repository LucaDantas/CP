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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

struct Edge
{
	int u, v, w;
} edges[2*MAXN];

vector<pii> g[MAXN];

ll dist[MAXN][4]; // 0 -> s, 1 -> t, 2 -> u, 3 -> v

void dijkstra(int s, int k) {
	rep(i,0,MAXN) dist[i][k] = inf;
	
	priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
	
	q.push({0ll, s});
	dist[s][k] = 0;
	
	bool mark[MAXN]; clr(mark, 0);

	while(!q.empty()) {
		int u = q.top().ss;
		q.pop();

		if(mark[u]) continue;
		mark[u] = 1;

		for(auto nxt : g[u]) {
			int v = nxt.ff, w = nxt.ss;
			if(dist[v][k] > dist[u][k] + 1ll*w) {
				dist[v][k] = dist[u][k] + 1ll*w;
				q.push({dist[v][k], v});
			}
		}
	}
}

vi dag[MAXN], inv_dag[MAXN], ord;

bool mark[MAXN];

void dfs(int u) {
	mark[u] = 1;
	for(auto v : dag[u])
		if(!mark[v])
			dfs(v);
	ord.pb(u);
}

int main() {
	int n, m, S, T, U, V; scanf("%d %d %d %d %d %d", &n, &m, &S, &T, &U, &V);
	rep(i,0,m) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		edges[i] = {a,b,w};
		g[a].pb({b,w});
		g[b].pb({a,w});
	}

	dijkstra(S,0);
	dijkstra(T,1);
	dijkstra(U,2);
	dijkstra(V,3);

	ll menor = dist[T][0];

	rep(i,0,m) {
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		if(dist[u][0] + 1ll*w + dist[v][1] == menor)
			dag[u].pb(v), inv_dag[v].pb(u);
		if(dist[v][0] + 1ll*w + dist[u][1] == menor)
			dag[v].pb(u), inv_dag[u].pb(v);
	}

	dfs(S);

	reverse(all(ord));

	vector<ll> d(n+1);
 
	rep(i,1,n+1) d[i] = dist[i][2];
 
	for(auto x : ord) {
		for(auto y : dag[x]) {
			dist[y][2] = min(dist[x][2], dist[y][2]);
		}
	}

	reverse(all(ord));
 
	for(auto x : ord) {
		for(auto y : inv_dag[x]) {
			d[y] = min(d[x], d[y]);
		}
	}
 
	ll ans = inf;
 
	rep(i,1,n+1) {
		ans = min(ans, min(dist[i][2],d[i]) + dist[i][3]);
	}
 
	printf("%lld\n", ans);
}
