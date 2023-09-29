#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

vector<int> g[maxn][2];

vector<pair<int,int>> dist[maxn];

void reduz(vector<pair<int,int>>& a) {
    vector<pair<int,int>> aux;

    sort(a.begin(), a.end());

    int n = (int)(a.size());

    auto ccw = [](pair<int,int> base, pair<int,int> p1, pair<int,int> p2) {
        pair<int,int> a = {p1.first - base.first, p1.second - base.second},
            b = {p2.first - base.first, p2.second - base.second};
        return 1ll * a.first * b.second - 1ll * a.second * b.first > 0;
    };

    for(int i = 0; i < n; i++) {
        while(aux.size() >= 2 && !ccw(aux[(int)(aux.size())-2], aux[(int)(aux.size())-1], a[i]))
            aux.pop_back();
        aux.push_back(a[i]);
    }

    a = aux;
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0, u, v, c; i < m; i++)
        scanf("%d %d %d", &u, &v, &c), g[u][c].push_back(v);
    dist[1] = {{0, 0}};
    for(int u = 1; u <= n; u++) {
        reduz(dist[u]);

        for(auto [a, b] : dist[u]) {
            for(int v : g[u][0])
                dist[v].push_back({a+1, b});
            for(int v : g[u][1])
                dist[v].push_back({a, b+1});
        }
    }

    int q; scanf("%d", &q);
    while(q--) {
        int a, b, x; scanf("%d %d %d", &a, &b, &x);
        long long ans = 0x3f3f3f3f3f3f3f3f;
        for(auto [d1, d2] : dist[x])
            ans = min(ans, 1ll*d1*a + 1ll*d2*b);
        printf("%lld\n", ans);
    }
}
