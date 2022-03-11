#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10, mod = 1000000007;

int dp[2][maxn];

int main() {
	int n, k; scanf("%d %d", &n, &k);
	dp[0][0] = 1; --k; // já gasto um dia naturalmente que não conta
	for(int i = 0; i < n; i++) {
		for(int down = 0; down <= k; down++) {
			dp[1][down+1] += 1ll * (i - down) * dp[0][down] % mod;
			if(dp[1][down+1] >= mod) dp[1][down+1] -= mod;

			dp[1][down] += 1ll * (down + 1) * dp[0][down] % mod;
			if(dp[1][down] >= mod) dp[1][down] -= mod;
		}

		for(int down = 0; down <= k; down++)
			dp[0][down] = dp[1][down], dp[1][down] = 0;
	}
	printf("%d\n", dp[0][k]);
}
