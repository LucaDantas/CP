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
constexpr int maxn = 3e5 + 10;
constexpr int logn = 20;
constexpr int mod = 1000000007;

vector<pii> g[maxn];
int depth[maxn], tab[maxn][logn], pai[maxn][logn];

void dfs(int u, int p, int val) {
	depth[u] = depth[p] + 1;
	pai[u][0] = p;
	tab[u][0] = val;
	for(auto v : g[u])
		if(v.ff != p)
			dfs(v.ff, u, v.ss);
}

int LCA(int a, int b) {
	if(a == b) return a;
	if(depth[a] < depth[b]) swap(a, b);
	dec(i,logn-1,0)
		if(depth[pai[a][i]] >= depth[b])
			a = pai[a][i];
	if(a == b) return a;
	dec(i,logn-1,0)
		if(pai[a][i] != pai[b][i])
			a = pai[a][i], b = pai[b][i];
	return pai[a][0];
}

int path(int a, int b) {
	int ans = inf;
	dec(i,logn-1,0)
		if(depth[pai[a][i]] >= depth[b])
			ans = min(ans, tab[a][i]), a = pai[a][i];
	return ans;
}

int main() {
	int n, trash; scanf("%d %d", &n, &trash);
	rep(i,1,n) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].pb({b, w});
		g[b].pb({a, w});
	}
	dfs(1, 0, inf);
	rep(j,1,logn) rep(i,1,n+1) pai[i][j] = pai[pai[i][j-1]][j-1];
	rep(j,1,logn) rep(i,1,n+1) tab[i][j] = min(tab[i][j-1], tab[pai[i][j-1]][j-1]);
	int q; scanf("%d", &q);
	while(q--) {
		int a, b; scanf("%d %d", &a, &b);
		int lca = LCA(a, b);
		printf("%d\n", min(path(a, lca), path(b, lca)));
	}
}
