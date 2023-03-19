#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

mt19937 rng(random_device{}());

int n, m;

vector<int> g1[maxn], g2[maxn], g_mat[2*maxn];

int sub_sz[maxn];

void dfs_pai(int u) {
    sub_sz[u] = 1;
    for(int v : g2[u]) {
        g2[v].erase(find(g2[v].begin(), g2[v].end(), u));
        dfs_pai(v);
        sub_sz[u] += sub_sz[v];
    }
}

bool dp[maxn][maxn][maxn], seen[maxn][maxn][maxn], mark[2*maxn];
int par[maxn*2];

bool dfs(int u) {
    mark[u] = 1;

    if(u > n)
        return !par[u] || dfs(par[u]);

    for(int v : g_mat[u]) if(!mark[v] && dfs(v))
        return (par[u] = v, par[v] = u, 1);

    return 0;
}

bool solve(int u1, int u2, int p) {
    if(sub_sz[u2] == 1) return dp[u1][u2][p] = 1;
    if(seen[u1][u2][p]) return dp[u1][u2][p];
    seen[u1][u2][p] = 1;

    auto add_edge = [](int v1, int v2) {
        g_mat[v1].push_back(v2 + n);
        g_mat[n + v2].push_back(v1);
    };

    vector<pair<int,int>> sv;

    for(int v1 : g1[u1]) if(v1 != p)
        for(int v2 : g2[u2])
            if(solve(v1, v2, u1))
                sv.emplace_back(v1, v2);

    for(int i = 1; i <= n+m; i++)
        g_mat[i].clear();

    for(auto [u, v] : sv)
        add_edge(u, v);

    for(int i = 1; i <= n+m; i++)
        shuffle(g_mat[i].begin(), g_mat[i].end(), rng);

    memset(par, 0, sizeof par);

    int ans = 0;
    for(int last = -1; ans > last;) {
        last = ans;
        memset(mark, 0, sizeof mark);
        for(int i = 1; i <= n; i++)
            if(!par[i] && !mark[i] && dfs(i))
                ++ans;
    }

    return dp[u1][u2][p] = (ans == g2[u2].size());
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g1[a].push_back(b), g1[b].push_back(a);
    scanf("%d", &m);
    for(int i = 1, a, b; i < m; i++)
        scanf("%d %d", &a, &b), g2[a].push_back(b), g2[b].push_back(a);
    dfs_pai(1);
    bool ok = 0;
    for(int i = 1; i <= n; i++)
        ok |= solve(i, 1, 0);
    puts(ok ? "Y" : "N");
}
