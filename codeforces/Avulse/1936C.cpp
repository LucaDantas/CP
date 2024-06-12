#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        vector<int> c(n);
        vector<vector<int>> a(n, vector<int>(m));
        for(int& x : c)
            scanf("%d", &x);
        for(auto& row : a)
            for(int& x : row)
                scanf("%d", &x);

        vector<vector<vector<pii>>> g(n, vector<vector<pii>>(m+1));

        for(int j = 0; j < m; j++) {
            vector<pii> lista;
            for(int i = 0; i < n; i++)
                lista.push_back({a[i][j], i});
            sort(lista.begin(), lista.end());

            for(int i = 1; i < n; i++) {
                g[lista[i-1].second][j].push_back({lista[i].second, 0});
                g[lista[i].second][j].push_back({lista[i-1].second, lista[i].first - lista[i-1].first});
            }
        }

        vector<vector<bool>> mark(n, vector<bool>(m+1, 0));
        vector<vector<long long>> dist(n, vector<long long>(m+1, inf));

        priority_queue<pair<long long,pii>, vector<pair<long long,pii>>, greater<pair<long long,pii>>> q;
        dist[0][m] = 0;
        q.push({0, {0, m}});

        while(q.size()) {
            auto [u, cor] = q.top().second;
            q.pop();
            if(mark[u][cor])
                continue;
            mark[u][cor] = 1;

            auto coloca = [&](int v, int w, int ci, int co) {
                if(dist[v][co] > dist[u][ci] + w) {
                    dist[v][co] = dist[u][ci] + w;
                    q.push({dist[v][co], {v, co}});
                }
            };

            for(auto [v, w] : g[u][cor])
                coloca(v, w, cor, cor);

            if(cor != m)
                coloca(u, c[u], cor, m);

            if(cor == m)
                for(int co = 0; co < m; co++)
                    coloca(u, 0, m, co);
        }

        printf("%lld\n", dist[n-1][m]);
    }
}
