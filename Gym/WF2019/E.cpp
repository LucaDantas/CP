#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

vector<int> g[maxn];
int grau[maxn], p[maxn];
bool ativo[maxn], arvore[maxn], folha[maxn], mark[maxn];

bool dfs(int u) {
    mark[u] = 1;
    for(int v : g[u]) if(v != p[u]) {
        if(mark[v]) return 0;
        p[v] = u;
        if(!dfs(v))
            return 0;
    }
    return 1;
}

void pinta(int u) {
    arvore[u] = 1;
    if(grau[u] == 1) folha[u] = 1;
    for(int v : g[u]) if(v != p[u]) {
        p[v] = u;
        pinta(v);
    }
}


int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0, a, b; i < m; i++)
        scanf("%d %d", &a, &b), ++grau[a], ++grau[b], g[a].push_back(b), g[b].push_back(a);
    queue<int> q;
    vector<pair<int,int>> ans;
    for(int i = 1; i <= n; i++) {
        if(!mark[i] && dfs(i)) pinta(i);
        if(grau[i] == 1 && !arvore[i]) q.push(i);
        if(folha[i]) ans.push_back({i, g[i][0]});
    }
    while(q.size()) {
        int u = q.front();
        q.pop();
        ativo[u] = 1;
        for(int v : g[u]) {
            if(grau[v] == 1) ativo[v] = 0;
            else {
                p[u] = v;
                if((--grau[v]) == 1) q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; i++)
        if(ativo[i])
            ans.push_back({p[i], i});
    printf("%ld\n", ans.size());
    sort(ans.begin(), ans.end());
    for(auto [u, v] : ans)
        printf("%d %d\n", u, v);
}
