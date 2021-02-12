#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define int long long

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

int dp[maxn], max_level[maxn][2]; // dp comigo sendo o vermelho
int depth[maxn], mx[maxn], mn[maxn], a[maxn], mx_depth;

vector<int> g[maxn], grp[maxn];

void dfs(int u, int p) {
	grp[depth[u]].pb(u);
	mx_depth = max(mx_depth, depth[u]);
	for(int v : g[u])
		if(v != p)
			depth[v] = depth[u]+1, dfs(v, u);
}

int32_t main() {
	int t; scanf("%lld", &t);
	while(t--) {
		int n; scanf("%lld", &n);
		mx_depth = 0;
		for(int i = 0; i <= n; i++)
			dp[i] = max_level[i][0] = mx[i] = depth[i] = 0, mn[i] = inf, max_level[i][1] = -inf, g[i].clear(), grp[i].clear();
		for(int i = 2, p; i <= n; i++)
			scanf("%lld", &p), g[p].pb(i), g[i].pb(p);
		for(int i = 2; i <= n; i++)
			scanf("%lld", &a[i]);
		dfs(1, 0);
		for(int i = mx_depth; i >= 0; i--) {
			for(int u : grp[i]) {
				mx[i] = max(mx[i], a[u]);
				mn[i] = min(mn[i], a[u]);
				for(int v : g[u]) {
					if(depth[v] < depth[u]) continue;
					dp[u] = max(dp[u], dp[v] + max(mx[i+1] - a[v], a[v] - mn[i+1])); // meu filho vermelho
					dp[u] = max(dp[u], max(max_level[i+1][0] - a[v],
						max_level[i+1][1] + a[v])); // meu filho azul
				}
				max_level[i][0] = max(max_level[i][0], dp[u] + a[u]);
				max_level[i][1] = max(max_level[i][1], dp[u] - a[u]);
			}
		}
		printf("%lld\n", dp[1]);
	}
}
