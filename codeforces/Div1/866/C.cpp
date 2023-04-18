#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<int> g[maxn];

int dist[maxn];
void dfs(int u, int p) {
    for(int v : g[u]) if(v != p)
        dist[v] = dist[u] + 1, dfs(v, u);
}

bool ok[maxn];
vector<int> bons;
void get(int u, int s, int p = 0) {
    ok[u] = u == s;
    for(int v : g[u]) if(v != p)
        get(v, s, u), ok[u] |= ok[v];
    if(ok[u])
        bons.push_back(u);
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
    dfs(1, 0);
    int l = max_element(dist+1, dist+1+n) - dist;
    dist[l] = 0;
    dfs(l, 0);
    int r = max_element(dist+1, dist+1+n) - dist;
    get(l, r);
    vector<int> ans;
    for(int i = 0; i < (int)(bons.size()); i++) {
        if(!(i&1))
            ans.push_back(bons[i]);
        else
            for(int v : g[bons[i]])
                if(!ok[v]) ans.push_back(v);
    }
    for(int i = (int)(bons.size())-1; i >= 0; i--) {
        if(i&1)
            ans.push_back(bons[i]);
        else
            for(int v : g[bons[i]])
                if(!ok[v]) ans.push_back(v);
    }
    if(ans.size() == n) {
        puts("YES");
        for(int x : ans)
            printf("%d ", x);
        puts("");
    } else
        puts("NO");
}
