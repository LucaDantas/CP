#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 55, maxv = maxn*maxn*maxn;

vector<pair<int,int>> g[maxn];

int dp[maxn][maxn], dist[maxn][maxn];
bool leaf[maxn];

void dfs(int u, int p, int dd[]) {
    for(auto [v, w] : g[u]) if(v != p) {
        dd[v] = dd[u] + w;
        dfs(v, u, dd);
    }
}

int ruins[maxn];
vector<int> folhas[maxn]; // folhas de uma subarvore saindo de onde a policia comeca

void dfs2(int u, int p) {
    if(leaf[u]) folhas[u].push_back(u);
    for(auto [v, w] : g[u]) if(v != p) {
        dfs2(v, u);
        ruins[u] += ruins[v];
        for(int x : folhas[v])
            folhas[u].push_back(x);
    }
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for(int i = 1; i <= n; i++)
        dfs(i, 0, dist[i]);
    for(int i = 1; i <= n; i++)
        leaf[i] = g[i].size() == 1;

    int st; scanf("%d", &st);

    int m; scanf("%d", &m);
    for(int i = 0, x; i < m; i++)
        scanf("%d", &x), ++ruins[x];

    dfs2(st, 0);
    
    memset(dp, 0x3f, sizeof dp);
    for(int u = 1; u <= n; u++)
        dp[0][u] = 0;

    for(int alive = 1; alive <= m; alive++) {
        for(int u = 1; u <= n; u++) if(leaf[u]) {
            int l = 1, r = maxv; 
            while(l <= r) {
                int val = (l+r) >> 1, colocados = 0;
                for(int v = 1; v <= n; v++) if(v != u && leaf[v]) {
                    int qtd = 0;
                    while(qtd + colocados <= alive && dp[alive-qtd][v] + dist[u][v] >= val)
                        qtd++;
                    if(!qtd) colocados -= maxv;
                    colocados += qtd-1;
                }
                if(colocados >= alive) {
                    dp[alive][u] = val;
                    l = val+1;
                } else
                    r = val-1;
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for(auto [sub, w] : g[st]) {
        int alive = ruins[sub];
        int l = 1, r = maxv;
        int aq = 0x3f3f3f3f;

        while(l <= r) {
            int val = (l+r)>>1, colocados = 0;
            for(int v : folhas[sub]) {
                int qtd = 0;
                while(qtd + colocados <= alive && dp[m-qtd][v] + dist[st][v] >= val)
                    qtd++;
                if(!qtd) colocados -= maxv;
                colocados += qtd-1;
            }
            if(colocados >= alive) {
                aq = val;
                l = val+1;
            } else
                r = val-1;
        }
        ans = min(ans, aq);
    }
    
    printf("%d\n", ans);
}
