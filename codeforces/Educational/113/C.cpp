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
constexpr int mod = 998244353;

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int f[maxn], inv[maxn];

int choose(int a, int b) { return (int)(1ll * f[a] * inv[b] % mod * inv[a-b] % mod); }

void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

int ans(int n, int qtd) {
	int ans = 0;
	for(int i = qtd+1; i <= n; i++)
		add(ans, (int)(1ll * choose(i-1, qtd-1) * f[qtd] % mod * f[n-qtd-1] % mod * (i-qtd) % mod));
	return ans;
}

int main() {
	f[0] = inv[0] = 1;
	for(int i = 1; i < maxn; i++)
		f[i] = (int)(1ll * f[i-1] * i % mod), inv[i] = power(f[i], mod-2);
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vector<int> a(n);
		for(int& x : a)
			scanf("%d", &x);
		sort(all(a));
		if(a[n-1] == a[n-2]) printf("%d\n", f[n]);
		else if(a[n-1] == a[n-2] + 1) {
			int qtd = 0;
			for(int i = 0; i < n; i++)
				qtd += a[i] == a[n-2];
			printf("%d\n", ans(n, qtd));
		} else puts("0");
	}
}
