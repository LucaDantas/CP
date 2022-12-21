#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

using pii = pair<int,int>;

int n, m, P, Q;
vector<vector<char>> a;
vector<pii> g[maxn];
long long dist[maxn];
bool mark[maxn];

int get(pii pos) { return 1 + (pos.first-1) * m + (pos.second - 1); }

void join(pii x, pii p1, pii p2, pii q1) {
    for(auto [pos, custo] : {make_pair(p1, P), make_pair(p2, P), make_pair(q1, Q)}) {
        if(pos.first < 1 || pos.second < 1 || a[pos.first][pos.second] == '#')
            continue;
        g[get(pos)].push_back({get(x), custo});
    }
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    memset(mark, 0, sizeof mark);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(a[i][j] == '.')
                dist[get(pii(i, j))] = 0, q.push({0, get(pii(i, j))});
    while(q.size()) {
        int u = q.top().second; q.pop();
        if(mark[u]) continue;
        mark[u] = 1;
        for(auto [v, w] : g[u])
            if(dist[v] > dist[u] + w)
                dist[v] = dist[u] + w, q.push({dist[v], v});
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &P, &Q);
    a.assign(n+3, vector<char>(m+3, '#'));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf(" %c", &a[i][j]);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(a[i][j] == 'L')
                join(pii(i, j), pii(i+1, j+1), pii(i-1, j+1), pii(i, j+2));
            else if(a[i][j] == 'R')
                join(pii(i, j), pii(i+1, j-1), pii(i-1, j-1), pii(i, j-2));
            else if(a[i][j] == 'D')
                join(pii(i, j), pii(i-1, j-1), pii(i-1, j+1), pii(i-2, j));
            else if(a[i][j] == 'U')
                join(pii(i, j), pii(i+1, j-1), pii(i+1, j+1), pii(i+2, j));
    dijkstra();
    
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            if(i>1) ans = min(ans, dist[get(pii(i, j))] + dist[get(pii(i-1, j))]);
            if(j>1) ans = min(ans, dist[get(pii(i, j))] + dist[get(pii(i, j-1))]);
        }
    printf("%lld\n", ans < 0x3f3f3f3f3f3f3f3f ? ans : -1);
}
