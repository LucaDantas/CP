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
#define db(a) cerr << "DEBUG ( " << #a << " == ", debug(a), cerr << ")\n"
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

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
constexpr int MAXN = 410;
constexpr int mod = 1000000007;

ll pref[MAXN], dp[MAXN][MAXN];

int main() {
	int n; scanf("%d", &n);
	vi a(n+1); rep(i,1,n+1) scanf("%d", &a[i]);
	rep(i,1,n+1) pref[i] = pref[i-1] + a[i];

	for(int i = n; i >= 1; i--) {
		for(int j = i+1; j <= n; j++) {
			ll add = inf;
			for(int k = i; k < j; k++) {
				add = min(add, dp[i][k] + dp[k+1][j]);
			}
			dp[i][j] = add + pref[j] - pref[i-1];
		}
	}
	printf("%lld\n", dp[1][n]);
}
