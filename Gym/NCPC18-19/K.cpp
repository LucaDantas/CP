#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e3+10, mod = 1e9+7;

int dp[maxn], f[maxn], choose[maxn][maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void solve() {
	for(int i = 1; i < maxn; i++) {
		choose[i][0] = choose[i][i] = 1;
		for(int j = 1; j < i; j++)
			choose[i][j] = (choose[i-1][j] + choose[i-1][j-1]) % mod;
	}
}

int main() {
	solve();
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 2; i <= k; i++) {
		dp[i] = (int)(1ll * i * power(i-1, n-1) % mod);
		for(int j = 2; j < i; j++) {
			dp[i] += mod - (int)(1ll * dp[j] * choose[i][j] % mod);
			if(dp[i] >= mod) dp[i] -= mod;
		}
	}
	printf("%d\n", dp[k]);
}
