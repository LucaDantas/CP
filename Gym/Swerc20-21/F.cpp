#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2050;

int dp[2][maxn]; // dp[i], quantas arvores com i folhas tem

int main() {
    int r, n, mod; scanf("%d %d %d", &r, &n, &mod);
    r = n - r + 1;
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        if(i != r) {
            for(int j = 0; j <= i; j++) {
                int nao_folhas = i - 2*j - 2*(i > r);
                dp[1][j] += (int)(1ll * dp[0][j] * j % mod), dp[1][j] %= mod; // escolhendo uma folha
                dp[1][j+1] += (int)(1ll * dp[0][j] * nao_folhas % mod), dp[1][j+1] %= mod; // escolhendo uma nao-folha
            }
        } else {
            for(int j = 0; j <= i; j++) {
                int nao_folhas = i - 2*j;
                if(j)
                    dp[1][j-1] += (int)(1ll * dp[0][j] * j % mod), dp[1][j-1] %= mod; // escolhendo uma folha
                dp[1][j] += (int)(1ll * dp[0][j] * nao_folhas % mod), dp[1][j] %= mod; // escolhendo uma nao-folha
            }
        }
        for(int j = 0; j <= i; j++)
            dp[0][j] = dp[1][j], dp[1][j] = 0;
    }
    int ans = 0;
    for(int i = 0; i <= n; i++)
        ans += dp[0][i], ans %= mod;
    printf("%d\n", ans);
}