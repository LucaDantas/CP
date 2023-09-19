#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct DSU {
    int pai[maxn], peso[maxn], cor[maxn];
    DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1, cor[i] = 0; }
    int find(int u) { return pai[u] == u ? u : find(pai[u]); }
    int get_cor(int u) { return cor[u] ^ (pai[u] == u ? 0 : get_cor(pai[u])); }
    bool join(int a, int b) {
        int ca = get_cor(a), cb = get_cor(b);
        a = find(a), b = find(b);
        if(a == b) return ca != cb;
        if(peso[a] < peso[b])
            swap(a, b);
        pai[b] = a;
        peso[a] += peso[b];
        cor[b] = 1^ca^cb;
        return 1;
    }
} dsu;

vector<int> g[maxn];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<array<int,3>> edges(m);
    for(auto &[w, a, b] : edges)
        scanf("%d %d %d", &a, &b, &w), g[a].push_back(w), g[b].push_back(w);
    sort(edges.begin(), edges.end());
    int ans = INT_MAX;
    for(auto [w, a, b] : edges) {
        if(!dsu.join(a, b)) {
            ans = w;
            break;
        }
    }
    for(int u = 1; u <= n; u++) if(g[u].size() >= 2) {
        sort(g[u].begin(), g[u].end());
        ans = min(ans, g[u][0] + g[u][1]);
    }
    printf("%d\n", ans);
}
