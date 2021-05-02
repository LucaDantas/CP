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
constexpr int maxn = 4e5 + 10;
constexpr int mod = 1000000007;

struct Frac
{
	long long a, b;
	Frac(long long _a, long long _b) : a(_a), b(_b) { reduce(); }
	Frac(Frac _a, Frac _b) {
		a = _a.a * _b.b;
		b = _a.b * _b.a;
		reduce();
	}
	inline void reduce() { long long g = __gcd(a, b); a /= g, b /= g; }
	bool operator<(const Frac& f) const { if(a != f.a) return a < f.a; return b < f.b; }
	void manda() { printf("%lld %lld\n", (long long)a, (long long)b); }
};

int t;
int depth[maxn];
bool mark[maxn];
vector<pii> g[maxn];

map<Frac, int> mp;

vector<pii> ans;

bool dfs(int u, int p = 0, int id = -1) {
	mark[u] = 1;
	depth[u] = depth[p]+1;
	int ativo = 0;
	for(auto pp : g[u]) {
		auto [v, ind] = pp;
		if(v == p) continue;
		if((mark[v] && depth[v] > depth[u]) || (!mark[v] && dfs(v, u, ind))) {
			if(!ativo) ativo = ind;
			else ans.push_back({ativo, ind}), ativo = 0;
		}
	}
	if(ativo > 0 && p) {
		ans.push_back({ativo, id});
		return 0;
	}
	return 1;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		long long a, b, c, d; scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		Frac x(Frac(a+b, b), Frac(c, d)), y(Frac(a, b), Frac(c+d, d));

		if(!mp.count(x)) mp[x] = ++t;
		if(!mp.count(y)) mp[y] = ++t;
		g[mp[x]].push_back({mp[y], i+1});
		g[mp[y]].push_back({mp[x], i+1});
	}

	for(int i = 1; i <= t; i++)
		if(!mark[i]) dfs(i);
	printf("%d\n", sz(ans));
	for(auto p : ans)
		printf("%d %d\n", p.first, p.second);
}
