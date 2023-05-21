#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10, mod = 1e9+7;

int dp[maxn];

int main() {
    int n; scanf("%d", &n);
    dp[0] = 1;
    for(int i = 1, mx = 0, last = 0; i <= n; i++) {
        int x; scanf("%d", &x);
        if(x > mx)
            mx = x, last = i;
        dp[i] = (dp[last-1] + dp[i-1]) % mod; // já faço a soma de prefixo 
    }
    printf("%d\n", (dp[n] - dp[n-1] + mod) % mod);
}
