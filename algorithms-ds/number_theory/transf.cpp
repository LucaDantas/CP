#include <bits/stdc++.h>
using namespace std;
#define int long long
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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b,a%b);
}

int lcm(int a, int b) {
	return a*(b/gcd(a,b));
}

ll brute(ll now, ll end, ll k) {
	int cnt = 0;
	while(now != end) {
		cnt++;
		ll best = 0;
		rep(i,2,k+1) {
			best = max(best, now%i);
		}
		now -= best;
		if(best == 0) now--;
	}
	return cnt;
}

ll game(ll a, ll b, ll k) {
	vector<pii> dp(a - b + 1);
	for(int i = 0; i <= a-b; i++) {
		dp[i] = make_pair(inf, b + i);
	}

	dp[0].ff = 0;
	for(int i = 1; i <= a-b; i++) {
		dp[i].ff = dp[i-1].ff + 1;
		for(int j = 2; j <= k; j++) {
			if(dp[i].ss - dp[i].ss%j - b < 0) continue;

			dp[i].ff = min(dp[i].ff, dp[dp[i].ss - dp[i].ss%j - b].ff + 1);
		}
	}
	return dp.back().ff;
}

int32_t main() {
	ll a, b, k;
	scanf("%lld %lld %lld", &a, &b, &k);
	int periodo = 1;
	rep(i,2,k+1) periodo = lcm(periodo, i);

	if(a-b <= 2*periodo) {
		cout << game(a, b, k) << '\n';
		return 0;
	}

	int start = 2*periodo;
	ll moves = brute(start, periodo, k);
	ll low_a = a - a%periodo, low_b = (b%periodo)? b - b%periodo + periodo : b;

	ll outro = game(low_b, b, k);
	ll ans = (low_a - low_b)/periodo;
	ans *= moves;
	cout << ans + brute(a,low_a, k) + outro << endl;
}
