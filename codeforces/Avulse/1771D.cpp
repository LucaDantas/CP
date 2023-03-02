#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e3+10;

int dp[maxn][maxn], prox[maxn][maxn];
char s[maxn];

vector<int> g[maxn];

void dfs(int u, int p, int s) {
    prox[u][s] = p;
    for(int v : g[u]) if(v != p)
        dfs(v, u, s);
}

void clear(int n) {
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        for(int j = 0; j <= n; j++)
            dp[i][j] = prox[i][j] = 0;
    }
}

int solve(int l, int r) {
    if(dp[l][r]) return dp[l][r];
    if(l == r) return 1;
    if(prox[l][r] == r) return 1 + (s[l-1] == s[r-1]);
    if(s[l-1] == s[r-1])
        return dp[l][r] = 2 + solve(prox[l][r], prox[r][l]);
    return dp[l][r] = max(solve(prox[l][r], r), solve(l, prox[r][l]));
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        clear(n);

        scanf(" %s", s);

        for(int i = 1, a, b; i < n; i++)
            scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

        for(int i = 1; i <= n; i++)
            dfs(i, 0, i);

        int ans = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                ans = max(ans, solve(i, j));

        printf("%d\n", ans);
   }
}
