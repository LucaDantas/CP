#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 4e5+10;

vector<int> g[maxn]; // preciso de cor e de vizinho

vector<pair<int,int>> edges[maxn];

int lca[maxn], deg[maxn], depth[maxn], cor_cima[maxn];
long long val[maxn];

set<pair<long long,int>> cores_no_lca[maxn], global;

void dfs(int u) {
    for(int v : g[u]) if(!depth[v])
        depth[v] = depth[u]+1, dfs(v);
}

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i < n; i++) {
        int u, v, w, c; scanf("%d %d %d %d", &u, &v, &w, &c);
        g[u].push_back(v);
        g[v].push_back(u);
        val[c] += w;
        edges[c].push_back({u, v});
    }

    depth[0] = maxn;
    depth[1] = 1;
    dfs(1);

    for(int c = 1; c <= n; c++) {
        int cnt = 0;
        bool ok = 1;
        int menor = 0; // depth[0] eh maxn ent n eh pra dar problema

        for(auto [u, v] : edges[c]) {
            menor = depth[menor] < depth[u] ? menor : u;
            menor = depth[menor] < depth[v] ? menor : v;

            int x = depth[u] > depth[v] ? u : v;
            cor_cima[x] = c;

            deg[u]++, deg[v]++;

            cnt += (deg[u] == 1) + (deg[v] == 1) - (deg[u] == 2) - (deg[v] == 2);
            ok &= deg[u] <= 2 && deg[v] <= 2;
        }

        ok &= cnt == 2;

        if(!ok) val[c] = 0;
        else lca[c] = menor;

        cores_no_lca[menor].insert({val[c], c});

        for(auto [u, v] : edges[c])
            deg[u] = deg[v] = 0;
    }

    for(int i = 1; i <= n; i++)
        if(cores_no_lca[i].size())
            global.insert(*cores_no_lca[i].rbegin());

    vector<int> matando(n+1), estado_node(n+1, 1);

    global.insert({0, -1});
    while(q--) {
        int p, x; scanf("%d %d", &p, &x);
        estado_node[x] = p;
        if(!p) {
            if(!matando[cor_cima[x]]) {
                int c = cor_cima[x];
                if(estado_node[lca[c]]) {
                    global.erase(*cores_no_lca[lca[c]].rbegin());
                    cores_no_lca[lca[c]].erase({val[c], c});
                    if(cores_no_lca[lca[c]].size())
                        global.insert(*cores_no_lca[lca[c]].rbegin());
                } else
                    cores_no_lca[lca[c]].erase({val[c], c});
            }
            matando[cor_cima[x]]++;
            if(cores_no_lca[x].size())
                global.erase(*cores_no_lca[x].rbegin());
        } else {
            if(!(--matando[cor_cima[x]])) {
                int c = cor_cima[x];
                if(estado_node[lca[c]]) {
                    if(cores_no_lca[lca[c]].size())
                        global.erase(*cores_no_lca[lca[c]].rbegin());
                    cores_no_lca[lca[c]].insert({val[c], c});
                    global.insert(*cores_no_lca[lca[c]].rbegin());
                } else
                    cores_no_lca[lca[c]].insert({val[c], c});
            }
            if(cores_no_lca[x].size())
                global.insert(*cores_no_lca[x].rbegin());
        }
        printf("%lld\n", global.rbegin()->first);
    }
}
