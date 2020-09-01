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
constexpr int mod = 998244353;

int fat[maxn], inv[maxn], inv_fat[maxn];

// m mod i == m - floor[m/i] * i
// m mod i === - floor[m/i] * i mod m
// multiplico por i^(-1) e (m mod i)^(-1)
// i^(-1) === - floor[m/i] * (m mod i)^(-1)

void calc() {
	fat[0] = fat[1] = inv[1] = inv_fat[1] = inv_fat[0] = 1;
	rep(i,2,maxn) {
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv[i] = mod - (int)(1ll * (mod/i) * inv[mod%i] % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}
}

int choose(int x, int y) {
	return (int)((1ll * fat[x] * inv_fat[y] % mod) * inv_fat[x - y] % mod);
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

int inside[maxn], pref[maxn][45], ans;
pii range[maxn], edge[25];

void pre(int n) {
	vector<pii> a; rep(i,1,n+1) a.pb(range[i]);
	sort(all(a));
	int ptr = 0;
	priority_queue<int, vector<int>, greater<int>> q;
	rep(i,1,n+1) {
		for(; ptr < n && a[ptr].ff <= i; ptr++)
			q.push(a[ptr].ss);
		while(q.size() && q.top() < i)
			q.pop();
		inside[i] = sz(q);
		if(sz(q) >= i)
			add_self(ans, choose(sz(q), i));
	}
}

// calcula os prefixos pra escolher i-k caras em cada nível
void brute(int n) {
	for(int k = 1; k <= 40; k++) {
		for(int i = 1; i <= n; i++) {
			pref[i][k] = pref[i-1][k];
			if(i >= k && inside[i] >= i)
				add_self(pref[i][k], choose(inside[i]-k, i-k));
		}
	}
}

int main() {
	calc();
	int n, m; scanf("%d %d", &n, &m);
	rep(i,1,n+1) {
		int l, r; scanf("%d %d", &l, &r);
		range[i] = {l, r};
	}
	rep(i,0,m) {
		int x, y; scanf("%d %d", &x, &y);
		edge[i] = {x, y};
	}
	pre(n); brute(n);
	for(int mask = 1; mask < (1 << m); mask++) {
		// a gente vai olhar todas as masks e vai escolher
		// esses caras nos valores que eles tão dentro
		// e usar inclusion-exclusion pra contar direito quantos caras apareceram
		int l = 0, r = 1e6;
		set<int> s;
		for(int i = 0; i < m; i++) {
			if(mask&(1 << i)) {
				int a = edge[i].ff, b = edge[i].ss;
				s.insert(a); s.insert(b);
				l = max({l, range[a].ff, range[b].ff});
				r = min({r, range[a].ss, range[b].ss});
			}
		}
		if(l > r) continue;
		int k = sz(s), tam = __builtin_popcount(mask);
		int v = 0;
		add_self(v, pref[r][k] - pref[l-1][k] + mod);
		if(tam&1) add_self(ans, mod - v);
		else add_self(ans, v);
	}
	printf("%d\n", ans);
}
