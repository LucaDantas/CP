#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
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
constexpr int MAXN = 4e5 + 10;
constexpr int mod = 1000000007;

ll power(ll b, int e) {
	ll ans = 1;
	while(e) {
		if(e&1) ans *= b, ans %= mod;
		b *= b;
		b %= mod;
		e >>= 1;
	}
	return ans;
}

ll inv(ll x) { return power(x, mod-2); }

ll fat[MAXN];

void calc() {
	fat[0] = 1;
	rep(i,1,MAXN) fat[i] = fat[i-1]*i%mod;
}

ll choose(int a, int b) {
	return (((fat[a] * inv(fat[b]))%mod) * inv(fat[a-b]))%mod;
}

int main() {
	calc();
	int h, w, n; scanf("%d %d %d", &h, &w, &n);
	vector<pii> a(n);
	rep(i,0,n) scanf("%d %d", &a[i].ss, &a[i].ff);
	sort(a.rbegin(), a.rend());

	vector<ll> dp(n);
	for(int i = 0; i < n; i++) {
		int x = a[i].ff, y = a[i].ss;
		dp[i] = choose(w-x + h-y, w-x)%mod;

		for(int j = 0; j < i; j++) {
			if(a[j].ss >= y) dp[i] -= (dp[j]*
				choose(a[j].ff - x + a[j].ss - y, a[j].ff - x))%mod, 
				dp[i] %= mod;
		}
		if(dp[i] < 0) dp[i] += mod;
	}

	ll ans = choose(w-1 + h-1, w-1);
	for(int i = 0; i < n; i++) {
		int x = a[i].ff, y = a[i].ss;
		ans -= choose(x-1 + y-1, x-1)*dp[i]%mod;
		if(ans < 0) ans += mod;
	}
	printf("%lld\n", ans);
}
