#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 45;

int c[maxn], m;
long long g[maxn];

map<long long, int> dp;

int solve(long long vivos) {
    if(!vivos) return 0;
    if(dp.count(vivos)) return dp[vivos];
    int eu = 63-__builtin_clzll(vivos);
    int ans = 0;
    for(int b = 0; b < m; b++)
        if(vivos & g[eu] & (1ll << b))
            ans = max(ans, solve((vivos | g[b]) ^ g[b]) + c[b]);
    return dp[vivos] = ans;
}

int main() {
    int n; scanf("%d %d", &n, &m);
    long long desativados = 0;
    int last = -1;
    for(int i = 0, x; i < n; i++) {
        scanf("%d", &x); x--; // quero deixar 0 indexado
        if(last != -1) {
            g[x] |= 1ll << last, g[last] |= 1ll << x;
            if(x == last)
                desativados |= 1ll<<x;
        } else
            desativados = 1ll<<x;
        last = x;
    }
    desativados |= 1ll<<last;
    int ans = 0;
    for(int i = 0; i < m; i++)
        scanf("%d", &c[i]), ans += c[i], g[i] |= 1ll<<i;
    printf("%d\n", ans - solve(((1ll<<m)-1) ^ desativados));
}
