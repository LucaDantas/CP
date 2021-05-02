#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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

int mark[maxn], t;
ll depth[maxn], ans[maxn];
vector<int> ord;
vector<pii> g[maxn], g_rev[maxn];

ll gcd(ll a, ll b) { return !b ? a : gcd(b, a%b); }

void dfs(int u) {
	mark[u] = 1;
	for(auto v : g[u]) mark[v.first] || (dfs(v.first),1);
	ord.pb(u);
}

void go(int u) {
	mark[u] = t;
	for(auto pp : g_rev[u]) {
		auto [v, w] = pp;
		if(mark[v] > 0 && mark[v] < t) continue;
		if(!mark[v]) depth[v] = depth[u]+w, go(v);
		else ans[t] = gcd(depth[u] + w - depth[v], ans[t]);
		// In case it is less than 0 we can simply take the absolute value
		// because x * (m-1) === -x (mod m) so it is always possible anyway
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].pb({b, w});
		g_rev[b].pb({a, w});
	}
	for(int i = 1; i <= n; i++) mark[i] || (dfs(i), 1);
	reverse(all(ord));
	memset(mark, 0, sizeof mark);
	for(int i = 0; i < n; i++) mark[ord[i]] || (++t && (go(ord[i]),1));
	int q; scanf("%d", &q);
	while(q--) {
		int v, s, T; scanf("%d %d %d", &v, &s, &T);
		puts(s % gcd(T, ans[mark[v]]) == 0 ? "YES" : "NO");
	}
}
