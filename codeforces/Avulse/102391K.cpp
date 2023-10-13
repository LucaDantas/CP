#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 250010, logn = 20;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

vector<pair<int,int>> tree[2][maxn];

struct LCA {
    // preciso pra achar a virtual tree na segunda arvore
    int p[logn][maxn], d[maxn], in[maxn], t;
    long long dist[maxn];

    void dfs(int u, vector<pair<int,int>> g[]) {
        for(int l = 1; l < logn; l++)
            p[l][u] = p[l-1][p[l-1][u]];

        in[u] = ++t;
        for(auto [v, w] : g[u]) if(v != p[0][u]) {
            d[v] = d[u]+1;
            dist[v] = dist[u] + w;
            p[0][v] = u;
            dfs(v, g);
        }
    }

    int lca(int a, int b) {
        if(d[a] < d[b])
            swap(a, b);
        for(int l = logn-1; l >= 0; l--)
            if(d[a] - (1<<l) >= d[b])
                a = p[l][a];
        if(a == b)
            return a;
        for(int l = logn-1; l >= 0; l--)
            if(p[l][a] != p[l][b])
                a = p[l][a], b = p[l][b];
        return p[0][a];
    }

    vector<int> get_virtual_tree(vector<int> v, vector<pair<int,long long>> g[]) { // retorna todos os vertices usados pra poder limpar dps
        sort(v.begin(), v.end(), [&](int a, int b) {
            return in[a] < in[b];
        });

        vector<int> aux = {v.front()};
        for(int i = 1; i < (int)(v.size()); i++) {
            aux.push_back(lca(v[i-1], v[i]));
            aux.push_back(v[i]);
        }

        sort(aux.begin(), aux.end(), [&](int a, int b) {
            return in[a] < in[b];
        });
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());

        for(int i = 1; i < (int)(aux.size()); i++) {
            int u = aux[i], pai = lca(aux[i-1], aux[i]);
            long long distancia = dist[u] - dist[pai];
            g[u].push_back({pai, distancia});
            g[pai].push_back({u, distancia});
        }

        return aux;
    }
} lca;

long long ans[maxn];

struct Centroid {
    int sz[maxn];
    bool mark[maxn]; // os que ja foram considerados como centroids
    long long cost[maxn];
    vector<pair<int,long long>> virtual_tree[maxn];
    void dfs1(int u, int p, vector<pair<int,int>> g[]) {
        sz[u] = 1;
        for(auto [v, w] : g[u]) if(v != p && !mark[v]) {
            dfs1(v, u, g);
            sz[u] += sz[v];
        }
    }
    int find(int u, vector<pair<int,int>> g[]) {
        for(auto [v, w] : g[u]) {
            if(!mark[v] && (sz[v]<<1) > sz[u]) {
                sz[u] -= sz[v];
                sz[v] += sz[u];
                return find(v, g);
            }
        }
        return u;
    }
    void dfs2(int u, int p, vector<pair<int,int>> g[], vector<int>& vis) {
        vis.push_back(u);
        for(auto [v, w] : g[u]) if(v != p && !mark[v]) {
            cost[v] = cost[u] + w;
            dfs2(v, u, g, vis);
        }
    }
    
    long long closest[maxn];
    void dfs3(int u, int p, vector<pair<int,long long>> g[]) {
        for(auto [v, w] : g[u]) if(v != p) {
            dfs3(v, u, g);
            closest[u] = min(closest[u], min(cost[v], closest[v]) + w);
        }
    }
    
    void dfs4(int u, int p, long long closest_cima, vector<pair<int,long long>> g[]) {
        long long pref = inf;
        vector<long long> suf(g[u].size()+1, inf);
        for(int i = (int)(g[u].size())-1; i >= 0; i--) {
            auto [v, w] = g[u][i];
            suf[i] = suf[i+1];
            if(v != p)
                suf[i] = min(suf[i], min(closest[v], cost[v]) + w);
        }
        int i = 0;
        for(auto [v, w] : g[u]) {
            i++;
            if(v != p) {
                long long aq = min({cost[u], min(pref, suf[i]), closest_cima}) + w;
                pref = min(pref, min(closest[v], cost[v]) + w);
                closest[v] = min(closest[v], aq);
                dfs4(v, u, aq, g);
            }
        }
    }
    
    void decompose(int c, vector<pair<int,int>> g[]) {
        dfs1(c, -1, g);
        c = find(c, g);
        // c agora eh o centroide
        cost[c] = 0;
        mark[c] = 1;
        vector<int> vis;
        dfs2(c, -1, g, vis);

        vector<int> parte_da_virtual = lca.get_virtual_tree(vis, virtual_tree);
        
        dfs3(c, -1, virtual_tree);
        dfs4(c, -1, inf, virtual_tree);

        for(int u : vis)
            ans[u] = min(ans[u], cost[u] + closest[u]);

        for(int u : vis)
            cost[u] = inf;
        for(int u : parte_da_virtual)
            virtual_tree[u].clear(), closest[u] = inf;

        for(auto [v, w] : g[c])
            if(!mark[v])
                decompose(v, g);
    }
    void start(int c, vector<pair<int,int>> g[]) {
        memset(ans, 0x3f, sizeof ans);
        memset(cost, 0x3f, sizeof cost);
        memset(closest, 0x3f, sizeof closest);
        decompose(c, g);
    }
} centroid;

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, a, b, w; i < n; i++)
        scanf("%d %d %d", &a, &b, &w), tree[0][a].push_back({b, w}), tree[0][b].push_back({a, w});
    for(int i = 1, a, b, w; i < n; i++)
        scanf("%d %d %d", &a, &b, &w), tree[1][a].push_back({b, w}), tree[1][b].push_back({a, w});
    lca.dfs(1, tree[1]);
    centroid.start(1, tree[0]);
    for(int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
}
