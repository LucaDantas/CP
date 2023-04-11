#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

bitset<maxn> dp;

vector<int> g[maxn];

int sz[maxn], val[maxn], n;

void calc_sz(int u, int p) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p)
        calc_sz(v, u), sz[u] += sz[v];
}

int get_c(int u) {
    for(int v : g[u])
        if(2*sz[v] > n)
            return (sz[u] -= sz[v], sz[v] += sz[u], get_c(v));
    return u;
}

int main() {
    scanf("%d", &n);
    for(int i = 2, p; i <= n; i++)
        scanf("%d", &p), g[p].push_back(i);
    calc_sz(1, 0);
    int c = get_c(1);
    long long pre = 0;
    for(int i = 1; i <= n; i++)
        pre += sz[i];

    for(int v : g[c])
        val[sz[v]]++;

    dp.set(0);
    for(int i = 1; i <= n; i++) {
        while(val[i] > 2)
            val[i] -= 2, val[2*i]++;
        while(val[i]--)
            dp |= (dp << i);
    }

    long long ans = pre;
    for(int i = 1; i <= n-1; i++)
        if(dp[i]) ans = max(ans, pre + 1ll * i * (n-1-i));
    printf("%lld\n", ans);
}
