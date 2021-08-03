#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e6 + 10, mod = 1000000007;

constexpr int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

constexpr int inv3 = power(3, mod-2);

int dp[maxn][3], f[maxn], fi[maxn], iv[maxn];

int choose(int a, int b) { return (int)(1ll * f[a] * fi[b] % mod * fi[a-b] % mod); }

int main() {
	f[0] = fi[0] = f[1] = fi[1] = iv[1] = 1;
	for(int i = 2; i < maxn; i++)
		f[i] = (int)(1ll * i * f[i-1] % mod), iv[i] = mod - (int)(1ll * (mod/i) * iv[mod%i] % mod), fi[i] = (int)(1ll * iv[i] * fi[i-1] % mod);
	int n, q; scanf("%d %d", &n, &q);

	dp[0][0] = dp[0][1] = dp[0][2] = n;

	for(int i = 1; i < 3*n; i++) {
		dp[i][0] = (int)(1ll * (choose(3*n, i+1) - 2ll * dp[i-1][0] - dp[i-1][1]) * inv3 % mod);
		if(dp[i][0] < 0) dp[i][0] += mod;

		dp[i][1] = (dp[i][0] + dp[i-1][0]) % mod;
		dp[i][2] = (dp[i][1] + dp[i-1][1]) % mod;
	}

	while(q--) {
		int x; scanf("%d", &x);
		printf("%d\n", (dp[x][0] + choose(3*n, x)) % mod);
	}
}


