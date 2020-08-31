#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int sz[maxn], aux=0, n;
ll val[maxn];
vi g[maxn];

void dfs(int u, int p) {
	sz[u] = 1;
	for(auto v : g[u]) {
		if(v != p)
			dfs(v, u), sz[u] += sz[v];
	}
}

void calc(int u, int p) {
	for(auto v : g[u]) {
		if(v != p) {
			val[aux++] = 1ll * sz[v] * (n-sz[v]);
			calc(v, u);
		}
	}
}

void SOLVE() {
	cin >> n;
	rep(i,1,n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	int m; cin >> m;

	vi pr(m);
	rep(i,0,m)
		cin >> pr[i];

	while(m < n-1) {
		pr.pb(1);
		m++;
	}
	
	sort(all(pr));
	
	while(m >= n) {
		assert(sz(pr) == m);
		int back = pr.back();
		pr.pop_back();
		*pr.rbegin() *= back;
		*pr.rbegin() %= mod;
		m--;
	}
	
	assert(m == n-1);
	assert(m == sz(pr));
	
	sort(all(pr));

	dfs(1, 0); calc(1, 0);
	assert(aux == n-1);
	sort(val, val+aux);
	ll ans = 0;
	dec(i,aux-1,0) {
		ans += (val[i] % mod) * (pr[i] % mod) % mod;
		ans %= mod;
	}
	cout << (ans+mod)%mod << '\n';
	aux = 0, ans = 0; pr.clear();
	rep(i,0,n+5) {
		g[i].clear();
		sz[i] = 0;
		val[i] = 0;
	}
}

int32_t main() {
	fast;
	int T; cin >> T;
	while(T--) SOLVE();
}
