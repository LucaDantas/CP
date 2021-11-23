#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)

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
constexpr int logn = 32;

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

inline int choose(int a, int b) { return (int)(1ll * fat[a] * (1ll * inv_fat[b] * inv_fat[a-b] % mod) % mod); }

int p2(int x) { int ans = 0; while(!(x & 1)) ++ans, x >>= 1; return ans; }

int grp[logn], qtd[logn], pot[maxn], dp[maxn];

int escolhe_par(int x) {
	int ans = 0;
	for(int i = 2; i <= x; i += 2)
		ans += choose(x, i), ans %= mod;
	return ans;
}

int main() {
	calc();
	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = (pot[i-1] << 1) % mod;
	int n; scanf("%d", &n);
	for(int i = 0, x; i < n; i++)
		scanf("%d", &x), ++grp[p2(x)];
	qtd[0] = pot[grp[0]] - 1; // todas somente com elementos impares dão certo (-1 porque não queremos vazio)
	for(int i = 1; i < logn; i++) {
		// db(i, grp[i], qtd[i], escolhe_par(grp[i]));

		qtd[i] = (int)(1ll * (pot[grp[i]]-1) * qtd[i-1] % mod); // escolho qualquer subconjunto do atual mas também escolho qualquer subconjunto do anterior que deu certo

		qtd[i] += escolhe_par(grp[i]); // tenho que escolher uma quantidade par de elementos do conjunto pra isso dar certo sem precisar de ngm do anterior
		qtd[i] %= mod;

		// db(i, qtd[i]);

		qtd[i] += qtd[i-1]; qtd[i] %= mod; // faz a prefix sum

		// db(qtd[i]);
	}

	printf("%d\n", qtd[logn-1]);
}
