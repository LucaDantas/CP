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
constexpr int MAXN = 110;
constexpr int MAXK = 1e5 + 10;
constexpr int mod = 1000000007;

int main() {
	int n, K; scanf("%d %d", &n, &K);
	vi a(n+1); rep(i,1,n+1) scanf("%d", &a[i]);
	
	vector<ll> dp(K+1), pref(K+1, 1);
	dp[0] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= K; j++) {
			// dp[i][j] gets the sum of the last a[i] values, because we can give
			// to that children any value between [0..a[i]]
			dp[j] = pref[j];
			if(j - a[i] - 1 >= 0) dp[j] -= pref[j - a[i] - 1];
			if(dp[j] < 0) dp[j] += mod;
		}

		pref[0] = dp[0];
		rep(j,1,K+1) pref[j] = (pref[j-1] + dp[j])%mod;
	}

	printf("%lld\n", dp[K]);
}
