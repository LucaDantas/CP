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
constexpr int maxn = 5e3 + 10;
constexpr int mod = 1000000007;

// Based on lucio's solution

// dp[i][j] = min cost of having the first i voters to vote for you when you
// already have j voting for you

ll dp[maxn][maxn];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vector<pii> a(n+1);
		rep(i,1,n+1)
			scanf("%d %d", &a[i].ff, &a[i].ss);

		sort(a.begin()+1, a.end());

		rep(i,0,n+2)
			dp[0][i] = 0; // having no one to pay left costs zero

		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= n; j++) {
				// just pay him adding him to the count of already voting
				// and then his value
				dp[i][j] = 1ll*a[i].ss + dp[i-1][j+1];

				if(a[i].ff <= j + i - 1) dp[i][j] = min(dp[i][j], dp[i-1][j]);
			}
		}

		printf("%lld\n", dp[n][0]);
	}
}
