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
constexpr int maxn = 510;
int mod;

// m mod i = m - i*floor(m/i)
// m mod i === - i*floor(m/i) mod m
// i^-1 === m - floor(m/i)*(m mod i)^-1 mod m

int fat[maxn], inv[maxn], inv_fat[maxn];

void calc() {
	fat[0] = fat[1] = inv[1] = inv_fat[0] = inv_fat[1] = 1;
	for(int i = 2; i < maxn; i++) {
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv[i] = mod - (int)(1ll * (mod/i) * inv[mod%i] % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}
}

inline int choose(int a, int b) {
	return (int)(1ll * fat[a] * (1ll * inv_fat[b] * inv_fat[a-b] % mod) % mod);
}

inline ll p(int x) { return 1ll * x * (x+1) / 2; }

int f[maxn], c[maxn], dp1[maxn][maxn], dp2[maxn][maxn];

int main() {
	int n, m; scanf("%d %d %d", &n, &m, &mod);
	calc();
	f[0] = 1;
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < i; j++) {
			f[i] += (int)((1ll * choose(i-1, j) * f[j] % mod) * f[i-1-j] % mod);
			if(f[i] >= mod) f[i] -= mod;
			c[i] += (int)((1ll * (i+1) * choose(i-1, j) % mod) *
				((1ll * f[j] * c[i-1-j] % mod) + (1ll * f[i-1-j] * c[j] % mod) % mod) % mod);
			if(c[i] >= mod) c[i] -= mod;
			c[i] += (int)((1ll * choose(i-1, j) * (p(j) + p(i-1-j)) % mod) *
				(1ll * f[j] * f[i-1-j] % mod) % mod);
			if(c[i] >= mod) c[i] -= mod;
		}
		f[i] = (int)(1ll * f[i] * (i+1) % mod);
	}
	dp1[0][0] = 1;
	for(int k = 1; k <= n; k++) {
		dp1[k][0] = 1;
		for(int i = 1; i <= min(m, k); i++) {
			dp1[k][i] = dp1[k-1][i];
			dp2[k][i] = dp2[k-1][i];
			for(int j = 1; j <= i; j++) {
				dp1[k][i] += (int)((1ll * f[j] * dp1[max(k-j-1, 0)][i-j] % mod) * choose(i, j) % mod);
				if(dp1[k][i] >= mod) dp1[k][i] -= mod;
				
				dp2[k][i] += (int)((1ll * c[j] * dp1[max(k-j-1, 0)][i-j] % mod) * choose(i, j) % mod);
				if(dp2[k][i] >= mod) dp2[k][i] -= mod;
				dp2[k][i] += (int)((1ll * f[j] * dp2[max(k-j-1, 0)][i-j] % mod) * choose(i, j) % mod);
				if(dp2[k][i] >= mod) dp2[k][i] -= mod;
			}
		}
	}
	printf("%d\n", dp2[n][m]);
}
