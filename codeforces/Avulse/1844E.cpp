#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);
        vector<vector<pair<int,int>>> g(n+m); // arestas sao do tipo ou da mesma cor ou cor diferente
        for(int i = 0; i < k; i++) {
            int x, y, x2, y2; scanf("%d %d %d %d", &x, &y, &x2, &y2);
            --x, --y, --x2, --y2;
            if(y2 == y+1) {
                g[x].push_back({y+n, 1});
                g[y+n].push_back({x, 1});
            } else {
                g[x].push_back({y-1+n, 0});
                g[y-1+n].push_back({x, 0});
            }
        }
        vector<int> cor(n+m, -1);
        bool ok = 1;
        function<void(int)> dfs = [&](int u) {
            for(auto [v, w] : g[u]) {
                if(cor[v] == -1)
                    cor[v] = cor[u] ^ w, dfs(v);
                else
                    ok &= cor[v] == (cor[u] ^ w);
            }
        };
        for(int i = 0; i < n+m; i++)
            if(cor[i] == -1)
                cor[i] = 0, dfs(i);
        puts(ok ? "YES" : "NO");
    }
}
