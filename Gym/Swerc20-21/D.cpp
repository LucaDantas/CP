#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int dist[maxn];
bool mark[maxn];

vector<pair<int,int>> g[maxn], edges;

int main() {
    int n, m, trash, mx; scanf("%d %d %d %d", &n, &m, &trash, &mx);
    for(int i = 0, a, b, c; i < m; i++)
        scanf("%d %d %d", &a, &b, &c), g[a].push_back({b, c}), g[b].push_back({a, c}), edges.push_back({a, b});
    
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0, 0});
    while(q.size()) {
        int u = q.top().second; q.pop();
        if(mark[u]) continue;
        mark[u] = 1;
        for(auto [v, c] : g[u])
            if(dist[v] > dist[u] + c)
                dist[v] = dist[u] + c, q.push({dist[v], v});
    }
    int ans = 0;
    for(auto [a, b] : edges)
        if(2*min(dist[a], dist[b]) < mx) // 2* porque tem q ir e voltar
            ++ans;
    printf("%d\n", ans);
}