#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10;

vector<int> original[maxn<<1], g[maxn], rev[maxn], reduzido[maxn], grupo_cor[maxn];

int cor[maxn<<1];

int par[maxn<<1], n;

bool mark[maxn<<1];

bool dfs(int u) {
    mark[u] = 1;

    if(u > n)
        return !par[u] || dfs(par[u]);

    for(int v : original[u])
        if(!mark[v] && dfs(v))
            return (par[u] = v, par[v] = u, 1);

    return 0;
}

void dfs2(int u) {
    mark[u] = 1;

    for(int v : original[u])
        if(!mark[par[v]])
            dfs2(par[v]);
}

void match() {
    bool ok = 1;
    while(ok) {
        ok = 0;
        memset(mark, 0, sizeof mark);
        for(int i = 1; i <= n; i++)
            if(!par[i]) ok |= dfs(i);
    }

    memset(mark, 0, sizeof mark);

    for(int i = 1; i <= n; i++)
        if(!par[i]) dfs2(i);

    vector<int> ruim;
    for(int i = 1; i <= n; i++)
        if(mark[i]) ruim.push_back(i);

    if(ruim.size()) {
        puts("NO");
        printf("%ld\n", ruim.size());
        for(int x : ruim)
            printf("%d ", x);
        puts("");
        exit(0);
    }
}

vector<int> vis;

void top1(int u) {
    mark[u] = 1;
    for(int v : g[u])
        if(!mark[v])
            top1(v);
    vis.push_back(u);
}

void top2(int u) {
    mark[u] = 1;
    for(int v : reduzido[u])
        if(!mark[v])
            top2(v);
    vis.push_back(u);
}

void color(int u) {
    grupo_cor[cor[u]].push_back(u);
    for(int v : rev[u])
        if(!cor[v])
            cor[v] = cor[u], color(v);
}

bitset<maxn> see[maxn];

int main() {
    int m; scanf("%d %d", &n, &m);
    for(int i = 0, a, b; i < m; i++)
        scanf("%d %d", &a, &b), original[a].push_back(b), original[b].push_back(a);

    match();

    for(int u = 1; u <= n; u++)
        for(int v : original[u]) if(v != par[u])
            g[u].push_back(par[v]), rev[par[v]].push_back(u);

    memset(mark, 0, sizeof mark);
    for(int i = 1; i <= n; i++)
        if(!mark[i]) top1(i);

    reverse(vis.begin(), vis.end());
    for(int x : vis) {
        if(!cor[x])
            cor[x] = x, color(x);
    }

    vector<pair<int,int>> ans;

    for(int i = 1; i <= n; i++) if(grupo_cor[i].size() > 1) {
        int sz = (int)(grupo_cor[i].size());
        for(int j = 0; j < sz; j++)
            ans.push_back({grupo_cor[i][j], grupo_cor[i][(j+1)%sz]});
    }

    for(int u = 1; u <= n; u++)
        for(int v : g[u])
            if(cor[u] != cor[v] && find(reduzido[cor[u]].begin(), reduzido[cor[u]].end(), cor[v]) == reduzido[cor[u]].end())
                reduzido[cor[u]].push_back(cor[v]);

    reverse(vis.begin(), vis.end());

    vector<int> idx(n+1);
    for(int i = 0; i < (int)(vis.size()); i++)
        idx[vis[i]] = i+1;

    for(int u : vis) {
        see[u][u] = 1;
        sort(reduzido[u].begin(), reduzido[u].end(), [&idx](int a, int b) {
            return idx[a] > idx[b];
        });
        for(int v : reduzido[u]) {
            if(!see[u][v])
                see[u] |= see[v], ans.push_back({u, v});
        }
    }

    puts("YES");
    printf("%ld\n", ans.size() + n);
    for(int u = 1; u <= n; u++)
        printf("%d %d\n", u, par[u]);
    for(auto [x, y] : ans)
        printf("%d %d\n", x, par[y]);
}
