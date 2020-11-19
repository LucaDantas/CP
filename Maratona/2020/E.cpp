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
constexpr int logn = 20;
constexpr int mod = 1000000007;

int p[maxn][logn], a[maxn], ans[maxn];
vector<int> g[maxn], q[maxn];

int find(int u, int lim) {
	for(int l = logn-1; l >= 0; l--)
		if(a[p[u][l]] <= lim)
			u = p[u][l];
	return u;
}

int bit[maxn];

void upd(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ret = 0;
	for(; x > 0; x -= x&-x)
		ret += bit[x];
	return ret;
}

void dfs(int u) {
	for(int x : q[u])
		upd(x, 1);
	ans[u] += query(a[u]);
	for(int v : g[u])
		dfs(v);
	for(int x : q[u])
		upd(x, -1);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i], &p[i][0]);
		if(i != 1)
			g[p[i][0]].pb(i);
	}
	a[0] = inf;
	p[1][0] = 0;
	for(int l = 1; l < logn; l++)
		for(int i = 1; i <= n; i++)
			p[i][l] = p[p[i][l-1]][l-1];
	for(int i = 1; i <= m; i++) {
		int s, l, r; scanf("%d %d %d", &s, &l, &r);
		s = find(s, r);
		q[s].pb(l);
	}
	dfs(1);
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
