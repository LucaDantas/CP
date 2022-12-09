#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, logn = 20, mod = 1e9+7;

vector<pair<int,int>> g[maxn];
int valor[maxn], h;
bool mark[maxn], ok = 1;

void limpar(int sz) {
    ok = 1;
    for(int i = 0; i <= sz; i++) {
        g[i].clear();
        mark[i] = 0;
    }
}

void dfs(int u) {
    mark[u] = 1;
    for(auto [v, w] : g[u]) if(!mark[v])
        valor[v] = (w - valor[u] + h) % h, dfs(v);
    else if((valor[u] + valor[v] - w)%h != 0)
        ok = 0;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d %d", &n, &m, &h);
        limpar(n+m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int x; scanf("%d", &x);
                if(x == -1) continue;
                x = (h-x) % h;
                g[i].push_back({j+n, x});
                g[j+n].push_back({i, x});
            }
        }

        int ans = 1;
        bool first = 1;
        for(int i = 0; i < n+m; i++) {
            if(!mark[i]) {
                if(!first)
                    ans = (int)(1ll * ans * h % mod);
                else
                    first = 0;
                dfs(i);
            }
        }

        printf("%d\n", ans * ok);
    }
}
