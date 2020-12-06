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
constexpr int maxn = 1e3 + 10;
constexpr int mod = 1000000007;

vector<int> g[maxn], gr[maxn], gcond[maxn], id[maxn], ord;

int mark[maxn], comp[maxn], cnt;

void dfs1(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(!mark[v])
			dfs1(v);
	ord.pb(u);
}

void dfs2(int u) {
	mark[u] = 1;
	id[cnt].pb(u);
	comp[u] = cnt;
	for(int v : gr[u])
		if(!mark[v])
			dfs2(v);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), gr[b].pb(a);
	
	for(int i = 1; i <= n; i++)
		if(!mark[i])
			dfs1(i);
	
	clr(mark, 0);
	reverse(all(ord));
	// db(ord);

	for(int u : ord)
		if(!mark[u])
			++cnt, dfs2(u);

	// for(int i = 1; i <= n; i++)
	// 	db(comp[i]);
	
	// for(int i = 1; i <= cnt; i++)
	// 	db(id[i]);
	
	for(int i = 1; i <= cnt; i++) {
		for(int u : id[i])
			for(int v : g[u])
				if(comp[v] != comp[u])
					gcond[i].pb(comp[v]);
	}
	int ans = 0;
	clr(mark, 0);
	for(int i = 1; i <= cnt; i++) {
		if(sz(id[i]) <= 3 && !mark[i]) {ans += sz(id[i]); continue;}
		for(int v : gcond[i])
			mark[v] = 1;
	}
	printf("%d\n", ans);
}
