#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

vector<pair<int,int>> g[maxn];

int dist[maxn], fudido[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);

        memset(dist, 0x3f, sizeof dist);
        for(int i = 0, x; i < k; i++)
            scanf("%d", &x), dist[x] = 0;

        for(int i = 1; i <= n; i++)
            scanf("%d", fudido+i);

        for(int i = 0, a, b, w; i < m; i++)
            scanf("%d %d %d", &a, &b, &w), g[a].push_back({b, w}), g[b].push_back({a, w});

        // dijsktra
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        for(int i = 1; i <= n; i++)
            if(!dist[i]) q.push({0, i}), fudido[i] = 0;

        while(q.size()) {
            auto [dd, u] = q.top(); q.pop();
            // printf("u %d dd %d fdd %d\n", u, dd, fudido[u]);
            --fudido[u];
            if(fudido[u] != -1) continue; // se for igual a -1 significa que era 0 antes de eu subtrair entao posso usar
            dist[u] = dd;

            for(auto [v, w] : g[u])
                if(fudido[v] >= 0)
                    q.push({dist[u] + w, v});
        }

        printf("%d\n", dist[1] == inf ? -1 : dist[1]);

        for(int i = 1; i <= n; i++)
            g[i].clear();
    }
}
