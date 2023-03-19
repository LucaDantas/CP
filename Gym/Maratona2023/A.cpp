#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010;

bitset<maxn> dp[maxn];

vector<int> g[maxn], rev[maxn];

bool mark[maxn], morre[maxn];

bool tem[maxn];

int cor[maxn], c;

vector<int> ord, comp[maxn];

void dfs(int u) {
    if(mark[u]) return;
    mark[u] = 1;
    for(int el : comp[u])
        for(int v : g[el])
            v = cor[v], dfs(v), dp[u] |= dp[v];
}

void dfs_in(int u) {
    mark[u] = 1;
    for(int v : g[u]) if(!mark[v])
        dfs_in(v);
    ord.push_back(u);
}

void find_scc(int u) {
    comp[c].push_back(u);
    cor[u] = c;
    mark[u] = 1;
    for(int v : rev[u]) if(!mark[v])
        find_scc(v);
}

int main() {
    int n; scanf("%d", &n);

    for(int i = 1, a, b; i <= n; i++)
        scanf("%d %d", &a, &b), g[i].push_back(a), g[i].push_back(b), rev[a].push_back(i), rev[b].push_back(i);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            comp[j].clear(), cor[j] = 0;

        ord.clear();

        memset(mark, 0, sizeof mark);
        mark[i] = 1;

        for(int j = 1; j <= n; j++)
            if(!mark[j]) dfs_in(j);
        reverse(ord.begin(), ord.end());

        memset(mark, 0, sizeof mark);
        mark[i] = 1;
        for(int j = 1; j <= n; j++)
            dp[j].reset();
        dp[i].set(i);
        cor[i] = i, comp[i].push_back(i);

        for(int j = 0; j < n-1; j++) {
            int x = ord[j];
            if(mark[x]) continue;
            c = x;

            find_scc(x);

            for(int opa : comp[x])
                dp[x].set(opa);
        }

        memset(mark, 0, sizeof mark);
        mark[i] = 1;

        for(int j = 1; j <= n && !morre[i]; j++) {
            if(cor[j] != j) continue;
            dfs(j);
            if(dp[j][i] && dp[j][g[i][0]] && dp[j][g[i][1]])
                morre[i] = 1;
        }
    }

    for(int i = 1; i <= n; i++)
        putchar(morre[i] ? 'Y' : 'N');
    puts("");
}
