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
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

ll kdn(vector<ll> a) {
	ll now = 0, ans = -inf;
	int n = sz(a);

	rep(i,0,n) {
		now += a[i];
		ans = max(ans, now);
		now = max(now, 0ll);
	}

	ans = max(ans, now);

	return ans;
}

int32_t main() {
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		vi a(n);
		rep(i,0,n) cin >> a[i];

		int pares = 0;
		for(int i = 0; i < n; i += 2) {
			pares += a[i];
		}

		int ans = 0;

		vi dif1, dif2;
		for(int i = 0; i+1 < n; i += 2) {
			dif1.pb(a[i+1] - a[i]);
		}
		for(int i = 1; i+1 < n; i += 2) {
			dif2.pb(a[i] - a[i+1]);
		}
		ans = max(kdn(dif1), kdn(dif2));
		db(dif1);
		db(dif2);
		cout << ans + pares << '\n';
	}
}