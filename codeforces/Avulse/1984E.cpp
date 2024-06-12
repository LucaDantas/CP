#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

vector<int> g[maxn];
int dp[maxn][2];
bool tem_folha[maxn][2];

void dfs(int u, int p = 0) {
    dp[u][1] = 1;
    dp[u][0] = 0;

    tem_folha[u][1] = 0;
    tem_folha[u][0] = g[u].size() == 1; // tem_folha significa que tem alguma folha nao no independent set

    for(int v : g[u]) if(v != p) {
        dfs(v, u);

        if(make_pair(dp[v][1], tem_folha[v][1]) >= make_pair(dp[v][0], tem_folha[v][0]))
            dp[u][0] += dp[v][1], tem_folha[u][0] |= tem_folha[v][1];
        else
            dp[u][0] += dp[v][0], tem_folha[u][0] |= tem_folha[v][0];

        dp[u][1] += dp[v][0];
        tem_folha[u][1] |= tem_folha[v][0];
    }

    g[u].clear(); // ja limpo pro proximo caso de teste
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);

        for(int i = 1, a, b; i < n; i++)
            scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);

        dfs(1);
        printf("%d\n", max(dp[1][0] + tem_folha[1][0], dp[1][1] + tem_folha[1][1]));
    }
}
