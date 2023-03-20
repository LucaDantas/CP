#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010, maxv = 1e6+1e5;

int v[maxn];

long long dp[maxv];

int main() {
    int n, s; scanf("%d %d", &n, &s);
    for(int i = 0; i < n; i++) {
        int w, c; scanf("%d %d", &w, &c);
        v[w] = max(v[w], c);
    }

    if(s <= 1000000) {
        for(int i = 0; i < s; i++)
            for(int j = 1; j <= 1000; j++)
                dp[i+j] = max(dp[i+j], dp[i] + v[j]);

        printf("%lld\n", dp[s]);
    } else {
        pair<int,int> melhor = {v[1], 1};
        for(int i = 2; i <= 1000; i++)
            if(1ll*melhor.second*v[i] > 1ll*melhor.first*i)
                melhor = {v[i], i};

        int x = melhor.second;
        for(int i = 1; i <= 1000; i++) {
            for(int rep = 1; rep < x; rep++)
                dp[i * rep % x] = max(dp[i * rep % x], 1ll*v[i]*rep - 1ll * (i * rep / x) * v[x]);
        }

        for(int i = 0; i < x; i++)
            for(int j = 0; j < x; j++)
                dp[(i+j) % x] = max(dp[(i+j) % x], dp[i] + dp[j] - (i+j >= x) * v[x]);

        long long ans = dp[0];
        for(int i = 0; i < x; i++)
            ans = max(ans, dp[i] - 1ll * (i > s%x) * v[x]);

        printf("%lld\n", ans + 1ll * (s / x) * v[x]);
    }
}
