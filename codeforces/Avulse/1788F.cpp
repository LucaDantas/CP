#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

vector<pair<int,int>> org[maxn], g[maxn];

void add_edge(int a, int b, int val) {
    g[a].push_back({b, val});
    g[b].push_back({a, val});
}

int cor[maxn], sz[maxn];

bool mark[maxn], valid = 1;

void dfs(int u) {
    mark[u] = 1;
    sz[u] = (org[u].size()&1);
    for(auto [v, val] : g[u]) if(!mark[v]) {
        cor[v] = cor[u]^val;
        dfs(v);
        sz[u] += sz[v];
    } else if (cor[v]^cor[u]^val) {
        valid = 0;
    }
}

int ans[maxn];

void calc_ans(int u, int p) {
    for(auto [v, id] : org[u]) if(v != p) {
        ans[id] = cor[u]^cor[v];
        calc_ans(v, u);
    }
}

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), org[a].push_back({b, i}), org[b].push_back({a, i});
    for(int i = 0, a, b, x; i < q; i++)
        scanf("%d %d %d", &a, &b, &x), add_edge(a, b, x);

    int odd = -1;
    for(int u = 1; u <= n; u++) if(!mark[u]) {
        cor[u] = 0;
        dfs(u);
        if(u != 1 && (sz[u]&1)) // nao pode ser u=1 porque o u tem q sempre ser 0
            odd = u;
    }

    int val = 0;
    for(int i = 1; i <= n; i++)
        val ^= (org[i].size()&1) ? cor[i] : 0;

    if(~odd) {
        memset(mark, 0, sizeof mark);
        cor[odd] = val;
        dfs(odd);
    }

    calc_ans(1, 0);

    if(!valid) puts("No");
    else {
        puts("Yes");
        for(int i = 1; i < n; i++)
            printf("%d ", ans[i]);
        puts("");
    }
}
