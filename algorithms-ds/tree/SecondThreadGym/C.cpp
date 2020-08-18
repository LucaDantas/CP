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

vi g[maxn];
int tab[maxn][logn], depth[maxn];

void dfs(int u, int p) {
	tab[u][0] = p;
	depth[u] = depth[p]+1;
	for(auto v : g[u]) {
		if(v != p)
			dfs(v, u);
	}
}

int LCA(int a, int b) {
	if(a == b) return a;
	if(depth[a] < depth[b]) swap(a, b);
	dec(i,logn-1,0)
		if(depth[tab[a][i]] >= depth[b])
			a = tab[a][i];
	if(a == b) return a;
	dec(i,logn-1,0)
		if(tab[a][i] != tab[b][i])
			a = tab[a][i], b = tab[b][i];
	return tab[a][0];
}

int jump(int u, int val) {
	dec(i,logn-1,0)
		if((1 << i) <= val)
			u = tab[u][i], val -= (1 << i);
	return u;
}

int main() {
	int n; scanf("%d", &n);
	rep(i,1,n) {int a, b; scanf("%d %d", &a, &b); g[a].pb(b); g[b].pb(a);}
	dfs(1, 0);
	rep(j,1,logn) rep(i,1,n+1) tab[i][j] = tab[tab[i][j-1]][j-1];
	int q; scanf("%d", &q);
	while(q--) {
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		int lca = LCA(a, b);
		if(depth[b] + depth[a] - 2*depth[lca] <= c) printf("%d\n", b);
		else {
			if(depth[a] - depth[lca] >= c) {
				printf("%d\n", jump(a, c));
			} else {
				int val = depth[b] - depth[lca] - (c - (depth[a] - depth[lca]));
				printf("%d\n", jump(b, val));
			}
		}
	}
}
