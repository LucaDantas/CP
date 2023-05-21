#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+10;

vector<int> g[maxn], inv[maxn], vis, comp[maxn];
bool mark[maxn];
int c[maxn], in[maxn], out[maxn];

void dfs_1(int u) {
    mark[u] = 1;
    for(int v : g[u])
        if(!mark[v]) dfs_1(v);
    vis.push_back(u);
}

void dfs_2(int u, int t) {
    mark[u] = 1;
    comp[t].push_back(u);
    c[u] = t;
    for(int v : inv[u])
        if(!mark[v]) dfs_2(v, t);
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0, a, b; i < m; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), inv[b].push_back(a);

    for(int i = 1; i <= n; i++)
        if(!mark[i])
            dfs_1(i);

    reverse(vis.begin(), vis.end());
    memset(mark, 0, sizeof mark);

    int t = 0;
    for(int i = 0; i < n; i++)
        if(!mark[vis[i]])
            dfs_2(vis[i], t++);

    for(int u = 1; u <= n; u++)
        for(int v : g[u])
            if(c[v] != c[u]) ++out[c[u]], ++in[c[v]];

    if(t == 1) return (puts("0"), 0);
    int a = 0, b = 0;
    for(int i = 0; i < t; i++)
        a += !in[i], b += !out[i];
    printf("%d\n", max(a, b));
}
