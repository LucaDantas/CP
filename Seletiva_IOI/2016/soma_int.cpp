#include<cstdio>
using namespace std;

constexpr int maxn = 5e5+10;
constexpr long long inf = 6e14L;

int a[maxn], cnt[maxn][2];
long long dp[maxn][2];

bool comp(long long a1, int a2, long long b1, int b2) {
	if(a1 != b1) return a1 > b1;
	return a2 < b2;
}

void check(long long lambda, int n) {
	for(int i = 1; i <= n+1; i++) {
		if(comp(dp[i-1][0] - lambda, cnt[i-1][0]+1, dp[i-1][1], cnt[i-1][1])) {
			dp[i][1] = dp[i-1][0] + a[i] - lambda;
			cnt[i][1] = cnt[i-1][0]+1;
		} else dp[i][1] = dp[i-1][1] + a[i], cnt[i][1] = cnt[i-1][1];
		
		if(comp(dp[i-1][1], cnt[i-1][1], dp[i-1][0], cnt[i-1][0]))
			dp[i][0] = dp[i-1][1], cnt[i][0] = cnt[i-1][1];
		else dp[i][0] = dp[i-1][0], cnt[i][0] = cnt[i-1][0];
	}
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	int qtd_pos = 0;
	long long sum_pos = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if(a[i] >= 0) ++qtd_pos, sum_pos += a[i];
	}
	if(qtd_pos <= k) {printf("%lld\n", sum_pos); return 0;}
	long long l = 0, r = inf, best = 0;
	dp[0][1] = -inf;
	while(l <= r) {
		long long m = (l+r) >> 1ll;
		check(m, n);
		if(cnt[n+1][0] <= k)
			best = m, r = m-1;
		else l = m+1;
	}
	check(best, n);
	printf("%lld\n", dp[n+1][0] + 1ll*best*k);
}
