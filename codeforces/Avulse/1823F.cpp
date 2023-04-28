#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, mod = 998244353;

vector<int> g[maxn];

bool mark[maxn];
int cnt[maxn], s, t;

void dfs1(int u, int p) {
    mark[u] = s == u;
    for(int v : g[u]) if(v != p)
        dfs1(v, u), mark[u] |= mark[v];
}

void dfs2(int u, int p) {
    cnt[u] += mark[u];
    for(int v : g[u]) if(v != p)
        cnt[v] += cnt[u], dfs2(v, u);
}

int main() {
    int n; scanf("%d %d %d", &n, &s, &t);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
    dfs1(t, 0);
    mark[t] = 0;
    dfs2(t, 0);
    for(int i = 1; i <= n; i++)
        printf("%d ", i == t ? 1 : (int)(1ll * g[i].size() * cnt[i] % mod));
    puts("");
}
