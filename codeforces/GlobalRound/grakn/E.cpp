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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

struct DSU
{
	int pai[maxn];
	DSU() {
		for(int i = 0; i < maxn; i++)
			pai[i] = i;
	}
	int find(int x) {
		if(pai[x] == x) return x;
		else return pai[x] = find(pai[x]);
	}
	void join(int a, int b) {
		a = find(a);
		b = find(b);
		pai[a] = b;
	}
} dsu;

struct Edge
{
	int u, v, w;
};

vector<Edge> g;

int main() {
	int m, n; scanf("%d %d", &m, &n);
	vector<int> a(m), b(n);
	for(auto& it : a)
		scanf("%d", &it);
	for(auto& it : b)
		scanf("%d", &it);
	ll ans = 0;
	for(int i = 0; i < m; i++) {
		int tam; scanf("%d", &tam);
		while(tam--) {
			int u; scanf("%d", &u); u--;
			g.pb({i, m+u, a[i] + b[u]});
			ans += a[i] + b[u];
		}
	}
	sort(all(g), [](Edge x, Edge y){
		return x.w > y.w;
	});
	for(auto e : g) {
		if(dsu.find(e.u) != dsu.find(e.v))
			dsu.join(e.u, e.v), ans -= e.w;
	}
	printf("%lld\n", ans);
}
