/* 
	
	Altas Aventuras - OBI 2010
	O(sqrt(n) * log(k))

	fast nice amazing agnez version

	dp[t][j] = max number of balloons we can test using t tests with k balloons
	dp[t][j] = dp[t-1][j] + dp[t-1][j-1] + 1

	This recurrence comes from the fact that we want to balance the division point
	in the regular n^2*k recurrence and by selecting exactly in the middle point
	in the left we'll have the maximum number of guys we can test with t-1 tests
	and j balloons, and in the right we'll have the maximum number of guys we can
	test with t-1 tests and j-1 ballons, since the one we're using popped.
	We add 1 because we need to count this ballon we've just tried

	To get the complexity we want we simply need to minimize K with log at the 
	beginning because if we have more than log we can binary search and it's optimal
	And if we have k == 1 just print n, otherwise if k >= 2 the answer <= O(sqrt(n))
	We can show this by working an formula for k == 2
	
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int maxn = 50000;
constexpr int logn = 32;

ll dp[maxn][logn];

int main() {
	int n, k; scanf("%d %d", &n, &k);

	if(k == 1) {printf("%d\n", n); return 0;}

	k = min(k, logn-1);
	for(int i = 1; i < maxn; i++) dp[i][1] = i;
	for(int i = 1; i < logn; i++) dp[1][i] = 1;

	for(int j = 2; j <= k; j++) {
		for(int t = 2; t*t <= n+100; t++) {
			dp[t][j] = dp[t-1][j] + dp[t-1][j-1] + 1;
		}
	}

	for(int i = 1; i < maxn; i++) {
		if(dp[i][k] >= n) {
			printf("%d\n", i); return 0;
		}
	}
}
