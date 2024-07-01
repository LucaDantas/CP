#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10, logn = 21;

int f[maxn][logn];

int head[maxn], dist[maxn], id_cycle[maxn], pos_cycle[maxn], mark[maxn], sz_cycle[maxn], add_cycle[maxn], add_node[maxn];

int grau[maxn];

bool on_cycle[maxn];

void dfs2(int u, int p) {
    sz_cycle[p]++;
    on_cycle[u] = 1;
    dist[u] = 0, id_cycle[u] = p, head[u] = u;
    if(f[u][0] == p) return;
    pos_cycle[f[u][0]] = pos_cycle[u]+1;
    dfs2(f[u][0], p);
}

void dfs1(int u) {
    mark[u] = 1;
    int v = f[u][0];
    if(mark[v] == 1) pos_cycle[u] = 1, dfs2(u, u);
    else if(mark[v] == 0) dfs1(v);
    if(!on_cycle[u]) {
        head[u] = head[v];
        dist[u] = dist[v]+1;
        id_cycle[u] = id_cycle[v];
    }
    mark[u] = 2;
}

int find(int u, int val) {
    for(int l = logn-1; l >= 0; l--)
        if(val >= (1 << l))
            u = f[u][l], val -= (1 << l);
    return u;
}

void dfs3(int u) {
    if(f[u][0] == id_cycle[u])
        return;
    add_node[f[u][0]] += add_node[u];
    dfs3(f[u][0]);
}

int main() {
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++)
        scanf("%d", &f[i][0]), grau[f[i][0]]++;
    for(int l = 1; l < logn; l++)
        for(int i = 1; i <= n; i++)
            f[i][l] = f[f[i][l-1]][l-1];
    for(int i = 1; i <= n; i++)
        if(!mark[i]) dfs1(i);
    for(int u = 1; u <= n; u++) {
        if(dist[u] + sz_cycle[id_cycle[u]]-1 <= k) {
            add_node[u]++;
            add_node[head[u]]--;
            add_cycle[id_cycle[u]]++;
        } else {
            int fim = find(u, k+1);
            add_node[u]++;
            add_node[fim]--;
            if(on_cycle[fim] && pos_cycle[fim] < pos_cycle[head[u]])
                add_node[id_cycle[u]]++;
        }
    }
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(!grau[i]) q.push(i);
    while(q.size()) {
        int u = q.front();
        q.pop();
        add_node[f[u][0]] += add_node[u];
        if(!(--grau[f[u][0]]))
            q.push(f[u][0]);
    }

    for(int u = 1; u <= n; u++)
        if(id_cycle[u] == u)
            dfs3(u);

    for(int i = 1; i <= n; i++)
        printf("%d\n", add_node[i] + (on_cycle[i] ? add_cycle[id_cycle[i]] : 0));
}
