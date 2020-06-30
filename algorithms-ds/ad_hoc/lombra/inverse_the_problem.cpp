#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using piii = pair<int, pii>;
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
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e3 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int a[MAXN][MAXN];
ll dist[MAXN][MAXN];

int pai[MAXN], peso[MAXN];

vector<pii> g[MAXN];

void init() {
	rep(i,0,MAXN) {
		pai[i] = i;
		peso[i] = 1;
	}
}

int find(int x) {
	if(pai[x] == x) return x;
	return pai[x] = find(pai[x]);
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) swap(x, y);
	pai[y] = x;
	peso[x] += peso[y];
}

void dfs(int u, int p, int s) {
	for(auto nxt : g[u]) {
		int v = nxt.ff, d = nxt.ss;
		if(v == p) continue;
		dist[s][v] = dist[s][u] + d;
		dfs(v,u,s);
	}
}

int main() {
	fast;
	int n; cin >> n;
	rep(i,0,n) rep(j,0,n) cin >> a[i][j];
	rep(i,0,n) if(a[i][i] != 0) {cout << "NO\n"; return 0;}
	rep(i,0,n) rep(j,0,n) if(a[i][j] != a[j][i] || (i != j && a[i][j] == 0)) {cout << "NO\n"; return 0;}

	vector<pii> top;
	rep(i,0,n) {
		rep(j,i+1,n) {
			top.emplace_back(make_pair(i,j));
		}
	}
	
	sort(all(top), [](const pii& x, const pii& y){
			return a[x.ff][x.ss] < a[y.ff][y.ss];
		});

	init();

	rep(i,0,sz(top)) {
		int u = top[i].ff, v = top[i].ss;
		int d = a[u][v];

		if(find(u) == find(v)) continue;

		merge(u, v);
		g[u].pb({v, d});
		g[v].pb({u, d});
	}
	
	rep(i,0,n) {
		dfs(i,-1,i);
	}
	
	rep(i,0,n) {
		rep(j,0,n) {
			if(a[i][j] != dist[i][j]) { cout << "NO\n"; return 0; }
		}
	}
	
	cout << "YES\n";
}
