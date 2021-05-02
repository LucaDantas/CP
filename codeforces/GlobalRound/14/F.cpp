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
constexpr int mod = 1000000007;

vector<pii> g[maxn];

ll dinero[maxn], x;

struct DSU
{
	int pai[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i; }
	int find(int a) { return pai[a] == a ? a : pai[a] = find(pai[a]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(sz(g[a]) < sz(g[b]))
			swap(a, b);
		pai[b] = a;
		dinero[a] += dinero[b] - x;
		for(const pii& gld : g[b])
			g[a].pb(gld);
	}
} dsu;

vector<int> arestas;

void dfs(int u) {
	db(u);
	// for(int i = 0; i < sz(g[u]); i++) {
	while(g[u].size()) {
		auto [v, id] = g[u].back();
		v = dsu.find(v);
		if(u == v) {g[u].pop_back(); continue;}
		if(dinero[u] + dinero[v] < x) break;
		g[u].pop_back();
		arestas.pb(id);
		dsu.join(u, v);
		u = dsu.find(u);
	}
}

pii opa[maxn];

bool foi[maxn];

int main() {
	int n, m; scanf("%d %d %lld", &n, &m, &x);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &dinero[i]);
	for(int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b), g[a].pb({b, i}), g[b].pb({a, i});
		opa[i] = {a, b};
	}
	for(int i = 1; i <= n; i++)
		if(i == dsu.find(i) && dinero[i] >= x) dfs(i);
	for(int i = 1; i <= n; i++) {
		if(i != dsu.find(i) || foi[i]) continue;
		for(int j = 0; j < sz(g[i]); j++) {
			int v = g[i][j].first;
			if(dsu.find(v) != i && dinero[i] + dinero[dsu.find(v)] >= x)
				arestas.pb(g[i][j].second), dsu.join(i, v), i = dsu.find(i), foi[i] = 1;
		}
	}
	int gld = dsu.find(1);
	for(int i = 2; i <= n; i++)
		if(dsu.find(i) != gld) return puts("NO"), 0;
	puts("YES");
	for(int animal : arestas)
		printf("%d\n", animal+1);
		// printf("%d %d\n", opa[animal].first, opa[animal].second);
}

	// for(int i = 1; i <= n; i++)
	// 	printf("%d ", dsu.find(i));
	// puts("");