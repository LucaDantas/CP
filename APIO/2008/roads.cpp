#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { debug(a.first); debug(a.second); }
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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

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
} concrete, final;

vector<pii> edges[2];

vector<pii> talvez;
vector<pair<pii,int>> usar;

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	int cc = n;
	concrete.init(n);
	final.init(n);
	rep(i,0,m) {
		int u, v, t; scanf("%d %d %d", &u, &v, &t);
		edges[t].pb({u,v});
		if(t == 1) {	
			concrete.join(u, v);
		}
	}
	rep(i,0,sz(edges[0])) {
		int u = edges[0][i].ff, v = edges[0][i].ss;
		if(final.find(u) == final.find(v)) continue;
		if(concrete.find(u) == concrete.find(v)) {
			talvez.pb(edges[0][i]);
		}
		else {
			final.join(u, v);
			usar.pb({edges[0][i],0});
			k--; cc--;
		}
	}
	if(k < 0) {
		puts("no solution");
		return 0;
	}
	while(k && sz(talvez)) {
		int u = talvez.back().ff, v = talvez.back().ss;
		talvez.pop_back();
		if(final.find(u) == final.find(v)) continue;
		usar.pb({{u,v}, 0});
		final.join(u,v);
		k--; cc--;
	}
	if(k) {
		puts("no solution");
		return 0;
	}
	rep(i,0,sz(edges[1])) {
		int u = edges[1][i].ff, v = edges[1][i].ss;
		if(final.find(u) == final.find(v)) continue;
		usar.pb({edges[1][i], 1});
		final.join(u,v); cc--;
	}
	if(cc > 1) {
		puts("no solution");
		return 0;
	}
	
	rep(i,0,sz(usar)) {
		printf("%d %d %d\n", usar[i].ff.ff, usar[i].ff.ss, usar[i].ss);
	}
}
