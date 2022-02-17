#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 4e5+10, logn = 30;

int dp[logn][maxn];

set<pair<int,int>> bom;

int main() {
	bool sp = 0;
    int n, m; scanf("%d %d", &n, &m);
	if(n > m) swap(n, m), sp = 1;
    int q; scanf("%d", &q);
    for(int i = 0; i < q; i++) {
        int l, r; scanf("%d %d", &l, &r);
		if(sp) swap(l, r);
        bom.insert({l, r});
    }
    for(int l = 0; l < logn; l++)
        for(int i = 0; i < maxn; i++)
            dp[l][i] = -0x3f3f3f3f;
    dp[0][1] = 1;
    for(int l = 0; l < logn-1; l++) {
        for(int a = 1; a <= n; a++) {
            if(dp[l][a] == -0x3f3f3f3f) continue;
            int b = dp[l][a] + bom.count({a, dp[l][a]});
            dp[l+1][a] = max(dp[l+1][a], min(m, b + a));
            dp[l+1][min(n, a+b)] = max(dp[l+1][min(n, a+b)], dp[l][a]);
        }
    }
    for(int l = 0; l < logn; l++)
        if(dp[l][n] == m) return printf("%d\n", l), 0;

    int b = dp[logn-1][n], ans = logn-1;
    while(b < m) b += n + bom.count({n, b}), ++ans;
    printf("%d\n", ans);
}
