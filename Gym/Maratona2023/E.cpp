#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010;

int l, r, k;

map<int, int> dp[maxn][maxn];

int dfs(int last) {
    if(l == 0 && r == 0)
        return 0;
    if(dp[min(l, r)][max(l, r)].count(last))
        return dp[min(l, r)][max(l, r)][last];
    int melhor = l+r;
    for(int sz = min(last-1, max(l, r)); sz >= 1 && melhor; sz--) if(sz != k) {
        if(r >= sz) {
            r -= sz;
            melhor = min(melhor, dfs(sz));
            r += sz;
        }

        if(!melhor) break;

        if(l >= sz) {
            l -= sz;
            melhor = min(melhor, dfs(sz));
            l += sz;
        }
    }
    return dp[min(l, r)][max(l, r)][last] = melhor;
}

int main() {
    int n; scanf("%d %d %d", &n, &k, &l); r = n - l - k;
    if(k == 1 && (l == 1 || r == 1)) {
        if(l == 1) l = 0;
        else if(r == 1) r = 0;
        printf("%d\n", 1 + dfs(n));
    } else
        printf("%d\n", dfs(n));
}
