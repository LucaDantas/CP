#include<bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr int maxn = 5e5+10;

struct DSU {
    int pai[maxn], peso[maxn];
    DSU() { iota(pai, pai+maxn, 0); }
    int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(peso[a] < peso[b])
            swap(a, b);
        pai[b] = a;
        peso[a] += peso[b];
        return 1;
    }
} dsu;

array<ll,3> edges[maxn];

vi g[maxn];

void add_edge(int a, int b) { g[a].push_back(b), g[b].push_back(a); }

vi path;

void dfs(int u, int p) {
    path.push_back(u);
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        path.push_back(u);
    }
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(ll i = 0, a, b, c; i < m; i++)
        scanf("%lld %lld %lld", &a, &b, &c), edges[i] = {c, a, b};
    sort(edges, edges+m);
    ll ans = 0;
    for(int i = 0; i < m; i++)
        if(dsu.join(edges[i][1], edges[i][2]))
            ans += edges[i][0], add_edge(edges[i][1], edges[i][2]);
    printf("%lld\n", ans<<1);
    dfs(1, 0);
    printf("%ld\n", path.size());
    for(int x : path)
        printf("%d ", x);
}
