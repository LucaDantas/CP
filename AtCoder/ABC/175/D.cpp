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
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int p[maxn], c[maxn], fam[maxn], aux;
bool mark[maxn];
vi head, sz;
vector<ll> cost;

void dfs(int u, int tam, ll cs) {
	mark[u] = 1;
	if(mark[p[u]])
		head.pb(u), sz.pb(tam+1), cost.pb(cs+c[u]), fam[u] = aux++;
	else
		dfs(p[u], tam+1, cs+c[u]), fam[u] = fam[p[u]];
}

ll dfs2(int u, int k) {
	if(!k) return 0;
	return max(0ll, dfs2(p[u], k-1)) + c[u];
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	rep(i,1,n+1) scanf("%d", &p[i]);
	rep(i,1,n+1) scanf("%d", &c[i]);
	rep(i,1,n+1)
		if(!mark[i]) dfs(i, 0, 0);
	ll ans = -inf;

	for(int i = 1; i <= n; i++) {
		if(cost[fam[i]] > 0) {
			ll normal = 1ll * cost[fam[i]] * (k / sz[fam[i]]);
			ans = max(ans, normal + dfs2(i, k % sz[fam[i]]));
			if(k >= sz[fam[i]])
				ans = max(ans, normal - cost[fam[i]] + dfs2(i, sz[fam[i]]));
		} else {
			ans = max(ans, dfs2(i, min(k, sz[fam[i]])));
		}
	}
	
	printf("%lld\n", ans);
}