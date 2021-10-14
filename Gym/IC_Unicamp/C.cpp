#include <cstdio>

constexpr int maxn = 1e6+10, mod = 1e9+7;

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int dp[maxn], inv[maxn];

int itv(int l, int r) { return ((r >= 0 ? dp[r] : 0) - (l > 0 ? dp[l-1] : 0) + mod) % mod; }

int main() {
	int N, L, R, c; scanf("%d %d %d %d", &N, &L, &R, &c);
	int sz = power(R-L+1, mod-2);
	for(int i = 1; i <= N; i++)
		dp[i] = (int)((1ll * itv(i-R, i-L) * c % mod * sz + c) % mod), dp[i] += dp[i-1], dp[i] %= mod;
	printf("%d\n", (dp[N] - dp[N-1] + mod) % mod);
}
