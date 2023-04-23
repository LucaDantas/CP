#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, logn = 20;

vector<int> g[maxn];

int p[maxn][logn], depth[maxn];

void dfs(int u) {
    depth[u] = depth[p[u][0]] + 1;

    for(int l = 1; l < logn; l++)
        p[u][l] = p[p[u][l-1]][l-1];

    for(int v : g[u]) if(v != p[u][0])
        p[v][0] = u, dfs(v);
}

int lca(int a, int b) {
    if(depth[a] > depth[b])
        swap(a, b);
    for(int l = logn-1; l >= 0; l--)
        if(depth[b] - (1<<l) >= depth[a])
            b = p[b][l];
    if(a == b) return a;
    for(int l = logn-1; l >= 0; l--)
        if(p[a][l] != p[b][l])
            a = p[a][l], b = p[b][l];
    return p[a][0]; // os pais sao iguais porque eu fui ate o ultimo que sao diferentes
}

int dist(int a, int b) { return depth[a] + depth[b] - 2*depth[lca(a, b)]; }

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
    dfs(1);
    while(q--) {
        int a, b; scanf("%d %d", &a, &b);
        int d = dist(a, b) + 1; // adiciono 1 porque quero contar incluso os dois fins
        printf("%lld\n", n + 1ll * d * (d-1) / 2);
    }
}




