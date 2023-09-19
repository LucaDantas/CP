#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n+1);
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        vector<vector<bool>> dp(n+1, vector<bool>(2*(n+1)));
        for(int i = 0; i <= n; i++)
            dp[i][0] = 1;
        vector<vector<int>> itv(n+1, vector<int>(n+1, -1));
        for(int l = 1; l <= n; l++) {
            vector<bool> nao(n+1);
            int menor = 0;
            auto get = [&]() {
                while(nao[menor])
                    menor++;
                return menor;
            };
            for(int r = l; r <= n; r++) {
                nao[a[r]] = 1;
                itv[l][r] = get();
            }
        }
        for(int i = 1; i <= n; i++) {
            auto combine = [&](vector<bool>& a, vector<bool>& b, int val) -> void {
                for(int i = 0; i <= 2*n+1; i++)
                    a[i ^ val] = b[i] || a[i ^ val];
            };
            dp[i] = dp[i-1];
            combine(dp[i], dp[i-1], itv[i][i]);
            for(int j = i-1; j >= 1; j--)
                if(itv[j][i] != itv[j][i-1] && itv[j][i] != itv[j+1][i])
                    combine(dp[i], dp[j-1], itv[j][i]);
        }
        int ans = 0;
        for(int i = 0; i <= 2*n+1; i++)
            if(dp[n][i])
                ans = max(ans, i);
        printf("%d\n", ans);
    }
}
