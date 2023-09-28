#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<pair<int,int>> g[maxn];

long long ans[maxn];

int sz[maxn];

long long now = 0;

void dfs1(int u, int p) {
    sz[u] = 1;
    for(auto [v, w] : g[u]) if(v != p) {
        dfs1(v, u);
        now += 1ll * sz[v] * w;
        sz[u] += sz[v];
    }
}

void mv(int u, int v, int w) {
    now -= 1ll * sz[v] * w;
    sz[u] -= sz[v];
    sz[v] += sz[u];
    now += 1ll * sz[u] * w;
}

void dfs2(int u, int p) {
    ans[u] = now;
    for(auto [v, w] : g[u]) if(v != p) {
        mv(u, v, w);
        dfs2(v, u);
        mv(v, u, w);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n);
        for(int& x : a)
            scanf("%d", &x);
        for(int i = 1, u, v; i < n; i++)
            scanf("%d %d", &u, &v), g[u].push_back({v, a[u-1]^a[v-1]}), g[v].push_back({u, a[u-1]^a[v-1]});
        dfs1(1, 0);
        dfs2(1, 0);
        for(int i = 1; i <= n; i++)
            printf("%lld ", ans[i]);
        puts("");

        for(int i = 1; i <= n; i++)
            g[i].clear(), sz[i] = 0, ans[i] = 0;
        now = 0;
    }
}
