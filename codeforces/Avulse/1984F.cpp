#include<bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

using ll = long long;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        vector<ll> a(n+2);
        char s[n+2];
        scanf(" %s", s+1); // 1-index
        for(int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        s[n+1] = 'S';

        set<ll> sums;
        for(int i = 0; i <= n; i++)
            sums.insert(a[i] + a[i+1]);

        ll ans = 0;
        for(ll sum : sums) {
            vector<vector<int>> dp(n+2, vector<int>(2));
            dp[0][0] = 1; // comecando com P eh valido, comecando com S nao

            for(int i = 1; i <= n+1; i++) {
                if(s[i] == 'P' || s[i] == '?') { // posso colocar um P no atual
                    if(llabs(a[i] - a[i-1]) <= m) // checando se posso colocar PP
                        dp[i][0] += dp[i-1][0], dp[i][0] %= mod;
                    if(llabs(a[i] + a[i-1] - sum) <= 2*m) // checando se posso colocar SP
                        dp[i][0] += dp[i-1][1], dp[i][0] %= mod;
                }

                if(s[i] == 'S' || s[i] == '?') { // posso colocar S no atual
                    if(llabs(a[i] - a[i-1]) <= m) // checando se posso colocar SS
                        dp[i][1] += dp[i-1][1], dp[i][1] %= mod;
                    if(a[i] + a[i-1] == sum) // checando se posso colocar SP
                        dp[i][1] += dp[i-1][0], dp[i][1] %= mod;
                }
            }

            ans += dp[n+1][0] + dp[n+1][1] % mod;
            ans %= mod;
        }

        printf("%lld\n", ans);
    }
}
