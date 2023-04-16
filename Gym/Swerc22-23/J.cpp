#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+110;

int n, m, k, c[maxn];

vector<int> g[maxn];

int get(int i, int qtd) { return i * (k+1) + qtd; }

int dist[maxn];

int bfs(int s) {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    queue<int> q; q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int v : g[u])
            if(dist[v] == 0x3f3f3f3f)
                dist[v] = dist[u] + 1, q.push(v);
    }
    return *max_element(dist, dist+n*(k+1));
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", c+i);
    for(int i = 0; i < n; i++)
        for(int qtd = 0; qtd < k; qtd++)
            g[get(i, qtd)].push_back(get(i, qtd+1)),
            g[get(i, qtd+1)].push_back(get(i, qtd));
    for(int i = 0, u, v; i < m; i++) {
        scanf("%d %d", &u, &v); --u, --v;
        for(int qtd = 0; qtd <= k; qtd++) {
            g[get(u, qtd)].push_back(get(v, c[u] == c[v] ? qtd : k - qtd)); // se for de cores diferentes vai pra mask oposta
            g[get(v, c[u] == c[v] ? qtd : k - qtd)].push_back(get(u, qtd));
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans = max(ans, bfs(get(i, 0)));
    printf("%d\n", ans);
}
