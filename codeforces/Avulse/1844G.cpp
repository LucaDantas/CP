#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, logn = 20, logmaxv = 60;
constexpr long long maxvalido = 1e13L;

vector<int> g[maxn];

int p[maxn][logn], depth[maxn], lca[maxn];

long long d[maxn];

long long val[maxn][logmaxv+1];

void dfs(int u) {
    for(int l = 1; l < logn; l++)
        p[u][l] = p[p[u][l-1]][l-1];
    for(int v : g[u])
        if(v != p[u][0])
            p[v][0] = u, depth[v] = depth[u]+1, dfs(v);
}

void pre_lca(int n) {
    for(int i = 2; i <= n; i++) {
        int a = i-1, b = i;
        if(depth[a] < depth[b])
            swap(a, b);
        for(int l = logn-1; l >= 0; l--)
            if(depth[a] - (1 << l) >= depth[b])
                a = p[a][l];
        if(a == b) {
            lca[i] = a;
            continue;
        }
        for(int l = logn-1; l >= 0; l--)
            if(p[a][l] != p[b][l])
                a = p[a][l], b = p[b][l];
        lca[i] = p[a][0];
    }
}

int main() {
    vector<pair<int,int>> edges;
    int n; scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a), edges.push_back({a, b});

    for(int i = 2; i <= n; i++)
        scanf("%lld", d+i);

    dfs(1);
    pre_lca(n);

    for(int l = 1; l <= logmaxv; l++)
        for(int i = 2; i <= n; i++)
            val[i][l] = (d[i] - val[i-1][l] + 2 * val[lca[i]][l-1] + (1ll << l)) % (1ll << l);

    vector<long long> ans;
    for(auto [a, b] : edges) {
        if(p[a][0] != b)
            swap(a, b);
        ans.push_back(val[a][logmaxv] - val[b][logmaxv]);
        if(ans.back() <= 0 || ans.back() > maxvalido)
            return puts("-1"), 0;
    }
    for(long long x : ans)
        printf("%lld ", x);
    puts("");
}
