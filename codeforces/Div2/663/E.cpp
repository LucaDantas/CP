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
constexpr int maxn = 5e5 + 10;
constexpr int mod = 1000000007;

vi g[maxn], path, level[maxn];
int mark[maxn], ok, want;

void dfs(int u) {
	path.pb(u);
	if(sz(path) >= want) {
		ok = 1;
		puts("PATH"); printf("%d\n", sz((path)));
		for(auto it : path)
			printf("%d ", it);
		printf("\n");
		return;
	}
	level[sz(path)].pb(u);
	mark[u] = 1;
	for(auto v : g[u]) {
		if(mark[v]) continue;
		dfs(v);
		if(ok) return;
	}
	path.pop_back();
}

void SOLVE() {
	int n, m; scanf("%d %d", &n, &m);
	want = (n+1)/2; ok = 0;
	rep(i,1,n+1) g[i].clear(), level[i].clear(), mark[i] = 0;
	path.clear();

	rep(i,0,m) {
		int u, v; scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}

	dfs(1);

	if(!ok) {
		puts("PAIRING");
		printf("%d\n", (want+1)/2);
		for(int i = 1; want > 0; i++) {
			while(sz(level[i]) >= 2 && want > 0) {
				want -= 2;
				printf("%d ", level[i].back());
				level[i].pop_back();
				printf("%d\n", level[i].back());
				level[i].pop_back();
			}
		}
	}
}

int main() {
	int t; scanf("%d", &t);
	while(t--) SOLVE();
}
