#include <bits/stdc++.h>
using namespace std;

// testando se a dp é convexa

using ll = long long;

constexpr int maxn = 1e5+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll dp[maxn][11], new_dp[maxn][11], a[maxn], b[maxn];

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	memset(new_dp, 0x3f, sizeof new_dp);
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		if(i&1) {
			for(int ab = 0; ab <= i/2; ab++) {
				for(int j = 0; j <= k; j++)
					new_dp[ab][j] = min({dp[ab][j] + a[i], dp[ab+1][j] + b[i],
						j?dp[ab][j-1]:inf, j?dp[ab+1][j-1]:inf});
			}
		} else {
			for(int ab = 0; ab <= i/2; ab++) {
				for(int j = 0; j <= k; j++)
					new_dp[ab][j] = min({ab?(dp[ab-1][j] + a[i]):inf, dp[ab][j] + b[i],
						j&&ab?dp[ab-1][j-1]:inf, j?dp[ab][j-1]:inf});
			}
		}
		for(int ab = 0; ab <= i/2; ab++) {
			for(int j = 0; j <= k; j++)
				dp[ab][j] = new_dp[ab][j], new_dp[ab][j] = inf;// printf("%d\n", dp[ab][j]);
		}
	}
	ll ans = inf;
	for(int j = 0; j <= k; j++)
		ans = min(ans, dp[0][k]);
	printf("%lld\n", ans);
}