#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

#define all(a) a.begin(), a.end()

vector<int> g[maxn];

bool mark[maxn]; // os marcados sao os que com certeza nao tem o vertice secreto
int sz[maxn], p[maxn];
int qtd_queries = 0;

bool query(int x) {
    ++qtd_queries;
    printf("? %d\n", x);
    fflush(stdout);
    int ans; scanf("%d", &ans);
    return ans;
}

void answer(int x) {
    printf("! %d\n", x);
    fflush(stdout);
}

void pre_pai(int u) {
    for(int v : g[u])
        if(v != p[u])
            p[v] = u, pre_pai(v);
}

void pre(int u) {
    sz[u] = 1;
    for(int v : g[u]) if(v != p[u] && !mark[v])
        pre(v), sz[u] += sz[v];
}

int find_centroid(int u, int total) {
    for(int v : g[u])
        if(v != p[u] && !mark[v] && sz[v]*2 > total)
            return find_centroid(v, total);
    return u;
}

void mata_folhas(int u) {
    bool tem = 0;
    for(int v : g[u])
        if(v != p[u] && !mark[v])
            mata_folhas(v), tem = 1;
    if(!tem)
        mark[u] = 1;
}

void bb(int u) {
    vector<int> caminho;
    while(u != 1)
        caminho.push_back(u), u = p[u];
    caminho.push_back(u);
    reverse(all(caminho));
    int l = 0, r = (int)(caminho.size())-1;
    while(l < r) {
        int m = (l+r+1)>>1;
        if(query(caminho[m]))
            l = m;
        else
            l = max(0, l-1), r = max(0, m-2);
    }
    answer(caminho[l]);
}

void solve(int root) {
    pre(root);
    if(sz[root] == 1) {
        // vou pra busca binaria dos pais, sei que ta em alguem acima de mim
        bb(root);
        return;
    }

    int c = find_centroid(root, sz[root]);
    if(c == root) {
        // setto o maior filho para ser c, que eh quem eu vou perguntar
        pair<int,int> mx = {-1, -1};
        for(int v : g[root])
            if(!mark[v] && v != p[root])
                mx = max(mx, {sz[v], v});
        c = mx.second;
    }

    // pergunto no centroid/maior filho
    bool qr = query(c);
    if(qr) {
        // o coiso ta na subarvore do queried, solve pra ele, fds os outros
        solve(c);
    } else {
        // mato todas as folhas e o centroid
        mata_folhas(root);
        mark[c] = 1;
        solve(root);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        for(int i = 1, a, b; i < n; i++)
            scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
        pre_pai(1);
        solve(1);
        memset(mark, 0, sizeof mark);
        memset(p, 0, sizeof p);
        for(int i = 1; i <= n; i++)
            g[i].clear();
        qtd_queries = 0;
    }
}
