#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 6e5+10, inf = 0x3f3f3f3f;

int a[maxn], dp[maxn], l[maxn], ans[maxn];

int main() {
    for(int i = 0; i < maxn; i++)
        dp[i] = -inf;
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        dp[n+1] = 0;

        for(int i = 1; i <= n; i++)
            scanf("%d", a+i);

        int mx = 0;
        for(int i = n; i >= 2; i--) {
            dp[i] = dp[i + a[i] + 1] + 1, l[i] = max(l[i + a[i] + 1], mx) + 1;

            // calculo a resposta pro i-1
            ans[i-1] = (dp[i] == a[i-1] ? 0 : (dp[i] > 0 || a[i-1] <= l[i]) ? 1 : 2);

            mx = max(mx, dp[i]);
        }

        for(int i = 1; i <= n-1; i++)
            printf("%d ", ans[i]);
        puts("");

        for(int i = 0; i <= n+1; i++)
            dp[i] = -inf, l[i] = 0;
    }
}
