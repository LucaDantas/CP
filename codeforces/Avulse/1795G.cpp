#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

constexpr int maxn = 1e5+10, SZ = maxn/6 + 10;

bitset<SZ> dp[maxn];

vector<int> org[maxn], g[maxn], top;

int deg[maxn];

void clean(int n) {
    for(int i = 0; i <= n; i++) {
        deg[i] = 0;
        org[i].clear();
        g[i].clear();
    }
    for(int i = 0; i <= n; i++)
        dp[i].reset();
    top.clear();
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);

        clean(n);

        for(int i = 1; i <= n; i++)
            scanf("%d", deg + i);

        for(int i = 0, a, b; i < m; i++)
            scanf("%d %d", &a, &b), org[a].push_back(b), org[b].push_back(a);

        {
            vector<int> aux;
            for(int i = 1; i <= n; i++)
                if(!deg[i]) aux.push_back(i);
            while(aux.size()) {
                int u = aux.back(); aux.pop_back();
                top.push_back(u);
                for(int v : org[u]) if(deg[v]) {
                    g[u].push_back(v), --deg[v];
                    if(!deg[v])
                        aux.push_back(v);
                }
            }
        }

        long long ans = 0;

        for(int i = 1; i <= n; i++)
            ans += n - i + 1; // eu adiciono 1 porque quando eu olho minha dp eu me visito entao eu ja me removo

        for(int rep = 0; rep < 6; rep++) {
            for(int i = n-1; i >= 0; i--) {
                int u = top[i];
                if(u / SZ == rep)
                    dp[u].set(u % SZ);
                for(int v : g[u])
                    dp[u] |= dp[v];

                ans -= (int)dp[u].count();
            }

            for(int i = 1; i <= n; i++)
                dp[i].reset();
        }

        printf("%lld\n", ans);
    }
}
