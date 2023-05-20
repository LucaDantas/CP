#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010, mod = 1e9+7;

int dp[maxn][maxn], pref[maxn][maxn];

int main() {
    int n, s; scanf("%d %d", &n, &s);
    dp[0][0] = 1;
    for(int i = 0; i <= s; i++)
        pref[0][i] = 1;
    for(int sum = 1; sum <= s; sum++) {
        for(int sz = 1; sz <= sum; sz++)
            dp[sum][sz] = pref[sum-sz][sz];

        int current_sum = dp[sum][0];
        pref[sum][0] = dp[sum][0];

        for(int sz = 1; sz <= s; sz++)
            current_sum += dp[sum][sz], current_sum %= mod, pref[sum][sz] = (pref[sum][sz-1] + current_sum) % mod;
    }
    printf("%d\n", dp[s][n]);
}
