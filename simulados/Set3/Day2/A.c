#include <stdio.h>
#include <assert.h>

#define maxn 1000010
#define inf 0x3f3f3f3f3f3f3f3f

long long min(long long a, long long b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }

long long dp[maxn], a[maxn];

int opt[maxn];

int main() {
	int n, s, ans = 0; scanf("%d %d", &n, &s); --s;
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), a[i] = max(a[i], i>1?a[i-1]+1:0);
	for(int i = 1; i <= n; i++) {
		dp[i-1] = max(dp[i-1], a[i]);
		dp[i] = inf;
		for(int j = opt[i-1]; j < i; j++) {
			if(dp[j] + 2ll*s + max(a[i] - dp[j] + 1, i-j) + (i - j) < dp[i])
				dp[i] = dp[j] + 2ll*s + max(a[i] - dp[j] + 1, i-j) + (i - j), opt[i] = j;
			else break;
		}
	}
	printf("%lld\n", dp[n]);
}