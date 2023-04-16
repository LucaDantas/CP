#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 310;

int dp[maxn][maxn], a[maxn], n, h; // dp[l][r]

int connect(int i, int j) { return min(h, (a[j] - a[i] + 1) / 2 - 1); }

int main() {
    scanf("%d %d", &n, &h);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    a[0] = -(int)(1e9 + 10);
    a[n+1] = (int)(2e9 + 10);
    for(int sz = 1; sz <= n; sz++) {
        for(int l = 1; l + sz - 1 <= n; l++) {
            int r = l + sz - 1;
            dp[l][r] = min(dp[l+1][r] + connect(l, r+1), dp[l][r-1] + connect(l-1, r));
            for(int m = l; m < r; m++)
                dp[l][r] = min(dp[l][r], dp[l][m-1] + connect(l-1, m) + dp[m+2][r] + connect(m+1, r+1));
        }
    }
    printf("%d\n", dp[1][n]);
}
