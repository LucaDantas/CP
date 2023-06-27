#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

long long ans[maxn];

vector<int> g[maxn], list_dist[maxn];

void dfs(int u, int p, int s, int dist) {
    list_dist[s].push_back(dist);
    for(int v : g[u]) if(v != p)
        dfs(v, u, s, dist+1);
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 1; i <= n; i++)
        dfs(i, 0, i, 0), sort(list_dist[i].begin(), list_dist[i].end());
    putchar('0');
    for(int sz = 1; sz <= n; sz++) {
        long long melhor = 0x3f3f3f3f3f3f3f3f;
        for(int i = 1; i <= n; i++)
            ans[i] += list_dist[i][sz-1], melhor = min(melhor, ans[i]);
        printf(" %lld", 1ll*(n-1)*sz - 2*melhor);
    }
    puts("");
}
