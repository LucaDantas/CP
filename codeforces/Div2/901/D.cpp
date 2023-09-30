#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

int dp[maxn], cnt[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        for(int i = 0; i <= n; i++)
            dp[i] = 0x3f3f3f3f, cnt[i] = 0;
        for(int i = 0, x; i < n; i++)
            scanf("%d", &x), cnt[min(x, n)]++;
        dp[n] = 0;
        for(int i = n-1; i >= 0; i--) {
            if(!cnt[i]) { dp[i] = 0; continue; }
            for(int j = i+1; j <= n; j++)
                dp[i] = min(1ll * dp[i], 1ll * dp[j] + (cnt[i]-1) * j + i);
        }
        printf("%d\n", dp[0]);
    }
}
