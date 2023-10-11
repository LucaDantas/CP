#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

int dp[2][maxn][maxn], a[maxn];

int main() {
    int n; scanf("%d", &n); n <<= 1;
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    for(int sz = 1; sz <= n; sz++) {
        for(int l = 0; l + sz - 1 < n; l++) {
            int r = l + sz - 1;
            if(!(sz&1))
                dp[0][l][r] = max(dp[1][l][r-1] + a[r], dp[1][l+1][r] + a[l]);
            else
                dp[1][l][r] = a[l] > a[r] ? (sz>1 ? dp[0][l+1][r] : 0) - a[l] : (sz>1 ? dp[0][l][r-1] : 0) - a[r];
        }
    }
    int soma = 1;
    int l = 0, r = n-1;
    puts("TECHNOBLADE NEVER DIES!");
    while(l <= r) {
        if(soma + dp[1][l+1][r] + a[l] > 0)
            soma += a[l] - (a[l+1] > a[r] ? a[l+1] : a[r]), putchar('L'), ++l;
        else
            soma += a[r] - (a[l] > a[r-1] ? a[l] : a[r-1]), putchar('R'), --r;
        if(a[l] > a[r]) ++l;
        else --r;
    }
    putchar('\n');
}
