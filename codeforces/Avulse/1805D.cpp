#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

vector<int> g[maxn];

int d[maxn], dmax[maxn], cnt[maxn], ans[maxn];

void dfs(int u, int p) {
    d[u] = d[p]+1;
    dmax[u] = max(dmax[u], d[u]);
    for(int v : g[u]) if(v != p)
        dfs(v, u);
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, u, v; i < n; i++)
        scanf("%d %d", &u, &v), g[u].push_back(v), g[v].push_back(u);
    d[0] = -1;
    dfs(1, 0);
    int u = max_element(d+1, d+n+1) - d;
    dfs(u, 0);
    int v = max_element(d+1, d+n+1) - d;
    dfs(v, 0);
    for(int i = 1; i <= n; i++)
        cnt[dmax[i]]++;
    bool foi = 0;
    int qtd = n;
    for(int i = n; i >= 1; i--)
        foi |= cnt[i], qtd -= cnt[i], ans[i] = qtd + foi;
    for(int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
}
