#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)((a).size())
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 5e4+10, logn = 16;

vector<array<int,2>> back; // the two backedges
vector<int> g[maxn];

int d[maxn], p[logn][maxn];

void dfs(int u, int pai) {
    d[u] = d[pai]+1;
    p[0][u] = pai;
    for(int l = 1; l < logn; l++)
        p[l][u] = p[l-1][p[l-1][u]];

    vector<int> apagar;
    for(int v : g[u]) if(v != pai) {
        if(d[v]) {
            apagar.push_back(v);
            if(d[u] > d[v])
                back.push_back({u, v});
        } else dfs(v, u);
    }
    for(int v : apagar)
        g[u].erase(find(all(g[u]), v));
}

int LCA(int a, int b) {
    if(d[a] < d[b])
        swap(a, b);
    for(int l = logn-1; l >= 0; l--)
        if(d[a] - (1<<l) >= d[b])
            a = p[l][a];
    if(a == b) return a;
    for(int l = logn-1; l >= 0; l--)
        if(p[l][a] != p[l][b])
            a = p[l][a], b = p[l][b];
    return p[0][a];
}

bool is_parent(int a, int b) { int lca = LCA(a, b); return lca == a || lca == b; }

bool comp(array<int,2> c1, array<int,2> c2) {
    auto [a, b] = c1; int lca1 = LCA(a, b);
    auto [x, y] = c2; int lca2 = LCA(x, y);
    if(d[lca1] < d[lca2])
        swap(a, x), swap(b, y), swap(lca1, lca2);
    return LCA(lca1, lca2) != lca2 || (LCA(lca1, x) != lca1 && LCA(lca1, y) != lca1);
}

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n+1; i++) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b), g[b].push_back(a);
    }
    dfs(1, 0);
    while(q--) {
        int a, b; scanf("%d %d", &a, &b);
        int ans = 1;
        // checa individualmente pra cada loop
        for(auto [x, y] : back)
            ans += comp({a, x}, {y, b}) || comp({a, y}, {x, b});
        // teste usando os dois ciclos
        bool ok = 0;
        for(int rep = 0; rep < 2; rep++, swap(back[0], back[1])) {
            for(int mask = 0; mask < 4; mask++) {
                int p1 = mask&1, p2 = (mask&2)>>1;
                vector<array<int,2>> caminhos;
                caminhos.push_back({a, back[0][p1]});
                caminhos.push_back({back[0][!p1], back[1][p2]});
                caminhos.push_back({back[1][!p2], b});
                if(comp(caminhos[0], caminhos[1]) && comp(caminhos[0], caminhos[2]) && comp(caminhos[1], caminhos[2]))
                    ok = 1;
            }
        }
        ans += ok;
        printf("%d\n", ans);
    }
}
