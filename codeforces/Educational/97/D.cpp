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
void debug() { cout << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cout << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cout << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
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

vector<int> g[maxn];

int dfs(int u) {
	int ans = 0;
	for(int v : g[u])
		ans = max(ans, 1+dfs(v));
	return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			g[i].clear();
		vector<int> a(n);
		for(int& x : a)
			scanf("%d", &x);
		vector<int> now;
		int ptr = 0;
		for(int i = 1; i < n; i++) {
			if(a[i] > a[i-1])
				now.pb(a[i]);
			else {
				for(int x : now)
					g[a[ptr]].pb(x);
				ptr++;
				now.clear();
				now.pb(a[i]);
			}
		}
		if(sz(now))
			for(int x : now)
				g[a[ptr]].pb(x);
		printf("%d\n", dfs(1));
	}
}
