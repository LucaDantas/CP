#include <bits/stdc++.h>
using namespace std;

long long dp[3];

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(long long i = 0, last = 0, a; i < n + q; i++) {
		scanf("%lld", &a);
		dp[2] = max(min(dp[1] + a, dp[0] + last), dp[0] + a);
		dp[0] = dp[1]; dp[1] = dp[2];
		last = a;
		if(i+1 >= n) printf("%lld\n", dp[1]);
	}
}