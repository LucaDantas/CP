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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

vi g[maxn];

int depth[maxn], in[maxn], out[maxn], aux;

ll bit[maxn];

void upd(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

ll query(int x) {
	ll ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

void dfs(int u, int p) {
	depth[u] = depth[p] + 1;
	in[u] = ++aux;
	for(auto v : g[u])
		if(v != p)
			dfs(v, u);
	out[u] = aux;
}

void SOLVE() {
	int n, q; scanf("%d %d", &n, &q);
	rep(i,1,n+1) g[i].clear();
	clr(in, 0); clr(out, 0); clr(depth, 0); aux = 0; clr(bit, 0);
	rep(i,1,n) {int a, b; scanf("%d %d", &a, &b); g[a].pb(b); g[b].pb(a);}
	dfs(1, 0);
	while(q--) {
		int a, b, x; scanf("%d %d %d", &a, &b, &x);
		if(!x) {
			if(depth[a] < depth[b]) swap(a, b);
			printf("%lld\n", abs(query(out[a]) - ((in[a]>1)?query(in[a]-1):0)));
		} else {
			upd(in[a], x); upd(in[b], -x);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) SOLVE();
}
