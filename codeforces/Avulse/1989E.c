#include <stdio.h>

#define maxn 200010
#define mod 998244353

int dp[maxn][12], soma[12];

int main() {
    int n, k; scanf("%d %d", &n, &k);
    dp[0][0] = soma[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = k; j >= 1; j--) {
            dp[i][j] = (1ll*soma[j-1] - (i > 2 && i != n ? dp[i-2][j-1] : 0) + mod
                + (j==k?1ll*soma[j] - (i > 2 && i != n ? dp[i-2][j] : 0) + mod : 0)) % mod;
            soma[j] += dp[i][j], soma[j] %= mod;
        }
    }
    printf("%d\n", dp[n][k]);
}
