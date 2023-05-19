#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9+7, maxn = 2e5+10;

int power(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (int)(1ll * ans * b % mod);
        b = (int)(1ll * b * b % mod);
        e >>= 1;
    }
    return ans;
}

vector<int> g[maxn];

int sz[maxn];

void dfs(int u, int p) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p)
        dfs(v, u), sz[u] += sz[v];
}

int f[maxn], invf[maxn];

void calc() {
    f[0] = invf[0] = 1;
    for(int i = 1; i < maxn; i++)
        f[i] = (int)(1ll * i * f[i-1] % mod);
    invf[maxn-1] = power(f[maxn-1], mod-2);
    for(int i = maxn-1; i > 0; i--)
        invf[i-1] = (int)(1ll * invf[i] * i % mod);
}

int choose(int a, int b) { return b > a ? 0 : (int)(1ll * f[a] * invf[b] % mod * invf[a-b] % mod); }

int main() {
    calc();
    int k, n; scanf("%d %d", &n, &k);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

    if(k&1)
        return (puts("1"), 0);

    dfs(1, 0);

    int ans = choose(n, k); // there is at least one centroid that is valid in each tree
    for(int i = 2; i <= n; i++)
        ans += (int)(1ll * choose(sz[i], k/2) * choose(n-sz[i], k/2) % mod), ans %= mod;
    printf("%d\n", (int)(1ll * ans * power(choose(n, k), mod-2) % mod));
}
