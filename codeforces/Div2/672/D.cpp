#include <bits/stdc++.h>
using namespace std;
#define int long long
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
constexpr int maxn = 5e5 + 10;
constexpr int mod = 998244353;

int fat[maxn], inv_fat[maxn], inv[maxn];

void calc() {
	inv[1] = fat[1] = fat[0] = inv_fat[0] = inv_fat[1] = 1;
	for(int i = 2; i < maxn; i++) {
		inv[i] = (int)(mod - (1ll * (mod/i) * inv[mod%i] % mod));
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}
}

int choose(int a, int b) {
	// a choose b
	assert(a >= b);
	return (int)((1ll * fat[a] * inv_fat[b] % mod) * inv_fat[a-b] % mod);
}


int32_t main() {
	calc();
	int n, k; scanf("%lld %lld", &n, &k);
	vector<pii> a(n);
	for(auto& it : a)
		scanf("%lld %lld", &it.ff, &it.ss);
	sort(all(a));
	priority_queue<int, vector<int>, greater<int>> q;
	int ans = 0;

	for(int i = 0; i < n; i++) {
		while(q.size() && q.top() < a[i].ff)
			q.pop();
		if((int)q.size() >= k-1) ans += choose((int)q.size(), k-1), ans %= mod;
		q.push(a[i].ss);
	}

	printf("%lld\n", ans);
}
