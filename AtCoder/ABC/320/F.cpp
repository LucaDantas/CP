#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 610;

int dp[maxn][maxn][maxn];

int x[maxn], p[maxn], f[maxn];

int main() {
    int n, h; scanf("%d %d", &n, &h);
    for(int i = 1; i <= n; i++)
        scanf("%d", x+i);
    for(int i = 1; i < n; i++)
        scanf("%d %d", p+i, f+i);
    memset(dp, 0x3f, sizeof dp);
    for(int i = 0; i <= h; i++)
        dp[n][i][i] = 0;
    for(int i = n-1; i >= 0; i--) {
        for(int comeca = 0; comeca <= h; comeca++) {
            for(int termina = 0; termina <= h; termina++) {
                int d = x[i+1]-x[i];

                int &here = dp[i][comeca][termina];
                if(comeca >= d)
                    here = dp[i+1][comeca-d][termina+d]; // nao faco nada

                // ativo o posto no inicio
                if(comeca + f[i] <= h && comeca + f[i] >= d)
                    here = min(here, dp[i+1][comeca+f[i]-d][termina+d] + p[i]);

                // ativo o posto no final
                if(comeca >= d && termina - f[i] >= 0)
                    here = min(here, dp[i+1][comeca-d][termina-f[i]+d] + p[i]);
            }
        }
        for(int comeca = 0; comeca <= h; comeca++)
            for(int termina = h; termina >= 0; termina--)
                dp[i][comeca+1][termina] = min(dp[i][comeca+1][termina], dp[i][comeca][termina]),
                dp[i][comeca][termina] = min(dp[i][comeca][termina+1], dp[i][comeca][termina]);
    }
    int ans = dp[0][h][0];
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
}
