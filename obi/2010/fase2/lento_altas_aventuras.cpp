#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

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
constexpr int maxn = 210;
constexpr int logn = 10;

// slow version

// dp[n][k] com transição O(n)
// dp[n][k] = min(all_i{1..n-1}(max(dp[i-1][j-1], dp[n-i][j]))) + 1
// dp[p][1] = p;

int dp[maxn][logn];

int main() {
	int N, k; scanf("%d %d", &N, &k);
	k = min(k, logn-1);
	rep(i,1,maxn) rep(j,2,logn) dp[i][j] = inf;
	rep(i,1,maxn) dp[i][1] = i;

	for(int j = 2; j <= k; j++) {
		for(int n = 0; n <= N; n++) {
			int& h = dp[n][j];
			for(int i = 1; i <= n; i++) {
				h = min(h, max(dp[i-1][j-1], dp[n-i][j]) + 1);
			}
		}
	}

	printf("%d\n", dp[N][k]);
}
