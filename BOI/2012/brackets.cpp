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
constexpr int MAXN = 3e4 + 10;
constexpr int mod = 1000000009;

char s[MAXN];

// ll dp[MAXN][MAXN];

int main() {
	int n; scanf("%d", &n);
	scanf(" %s", s);
	vector<bool> a(n);
	rep(i,0,n) {
		if(s[i] == '(') a[i] = 1;
		else a[i] = 0;
	}
	vector<int> dp(n+1), new_dp(n+1);
	dp[0] = 1;
	for(int i = 0; i < n; i++) {
		for(int j = !(i&1); j <= min(i+1,n-i-1); j+=2) {
			// if(i&(j&1)) {new_dp[j] = 0; continue;}
			// we get j open brackets by closing one from the (i-1,j+1) state
			new_dp[j] = dp[j+1];

			// we get j open brackets by opening one from the (i-1,j-1) state
			if(a[i] && j) new_dp[j] = (1ll*new_dp[j] + dp[j-1] >= mod)? 
				new_dp[j] - mod + dp[j-1] : new_dp[j] + dp[j-1];

			// Needed to optimize not to use mod operation nor long long
			// otherwise would get TLE, and also save memory using O(n) trick
		}
		swap(dp, new_dp);
	}
	printf("%d\n", dp[0]);
}
