#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1<<20, mod = 1e9+9;

int a[maxn];

void solve(int l, int r) {
    if(l == r-1) return;
    int m = (l+r) >> 1;
    for(int i = l; i < m; i++)
        a[i] += -a[m+i-l] + mod, a[i] %= mod;
    solve(l, m);
    solve(m, r);
}

int main() {
    int n; scanf("%d", &n); n = 1<<n;
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    solve(0, n);
    int ans = 1;
    for(int i = 0; i < n; i++)
        ans = (int)(1ll * ans * a[i] % mod);
    printf("%d\n", ans);
}
