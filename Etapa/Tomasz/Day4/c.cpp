#include <bits/stdc++.h>
using namespace std;
#define int ll
using ll = long long;
using pii = pair<int, int>;

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
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr long long inf = 0x3f3f3f3f3f3f;
constexpr int maxn = 2e5 + 10;

// primeiro é so de min
long long dp[maxn][2]; // [0, 1] -> apagou ou nao alguem
ll sz[maxn];
vector<pii> g[maxn];

ll val[maxn], perto[maxn], ans, k;

void dfs(int u, int p = 0) {
	if(sz(g[u]) == 1) return (void)(sz[u] = 1);
	ll opt = inf;
	perto[u] = inf;
	for(auto pp : g[u]) {
		int v = pp.ff;
		ll w = pp.ss;
		if(v == p) continue;
		dfs(v, u); sz[u] += sz[v];
		dp[v][!(sz[v]&1)] += w;
		dp[u][0] += dp[v][0];
		opt = min(opt, dp[v][1] - dp[v][0]);
		val[u] += val[v] + sz[v] * w;
		perto[u] = min(perto[u], perto[v] + w);
	}
	dp[u][1] = dp[u][0] + opt;
}

void dfs2(int u, int p = 0) {
	for(auto pp : g[u]) {
		int v = pp.ff;
		ll w = pp.ss;
		if(sz[v] > k/2 && v != p) {
			sz[u] -= sz[v];
			val[v] = val[u] + (sz[u]-sz[v]) * w;
			sz[v] += sz[u];
			perto[v] = min(perto[v], perto[u]+w);
			dfs2(v, u);
			return;
		}
	}
	ans = max(ans, val[u] - ((k&1) ? perto[u] : 0));
	for(auto pp : g[u]) {
		int v = pp.ff;
		ll w = pp.ss;
		if(sz[v] > k/2 && v != p) {
			sz[u] -= sz[v];
			val[v] = val[u] + (sz[u]-sz[v]) * w;
			sz[v] += sz[u];
			perto[v] = min(perto[v], perto[u]+w);
			dfs2(v, u);
			sz[v] -= sz[u];
			sz[u] += sz[v];
		}
	}
}

int32_t main() {
	int n; scanf("%lld", &n);
	for(int i = 1, a, b, c; i < n; i++)
		scanf("%lld %lld %lld", &a, &b, &c), g[a].pb({b, c}), g[b].pb({a, c});
	if(n == 1) return puts("0\n0"), 0;
	if(n == 2) return printf("%lld\n%lld\n", g[1][0].second, g[1][0].second), 0;
	int c = g[1].size() == 1 ? g[1][0].first : 1;
	dfs(c);
	printf("%lld\n", dp[c][sz[c]&1]);
	k = sz[c];
	dfs2(c);
	printf("%lld\n", ans);
}

