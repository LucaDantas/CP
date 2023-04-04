#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

vector<int> g[maxn];

int a[maxn];

map<int,vector<int>> cnt;

struct Edges {
    int u, v;
} edges[maxn];

map<pair<int,int>, int> ans;

int p_path[maxn], depth[maxn], p[maxn];

bool dfs1(int u, int ans_now, int dest) {
    bool ok = u == dest;

    for(int v : g[u]) if(v != p[u]) {
        p[v] = u;
        depth[v] = depth[u] + 1;
        ok |= dfs1(v, ans_now, dest);
    }

    if(ok) p_path[u] = u;
    else ans[{u, p[u]}] = ans_now;

    return ok;
}

void dfs2(int u) {
    for(int v : g[u]) if(!p_path[v])
        p_path[v] = p_path[u], dfs2(v);
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, u, v; i < n; i++)
        scanf("%d %d", &u, &v), g[u].push_back(v), g[v].push_back(u), edges[i] = {u, v};
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i), cnt[-a[i]].push_back(i);
    int u = 0, v = 0;
    for(auto it : cnt) {
        if(it.second.size() < 2) continue;
        if(it.second.size() >= 3) {
            for(int i = 1; i < n; i++) {
                auto [x, y] = edges[i];
                printf("%d\n", max({ans[{x, y}], ans[{y, x}], -it.first}));
            }
            return 0;
        }
        if(!u) {
            u = it.second[0], v = it.second[1];
            dfs1(u, -it.first, v);
            for(int i = 1; i <= n; i++)
                if(p_path[i])
                    dfs2(i);
        } else {
            int aq = -it.first;
            int pu = p_path[it.second[0]], pv = p_path[it.second[1]];
            if(depth[pu] > depth[pv])
                swap(pu, pv);
            if(depth[pu] > depth[u]) {
                int aux = depth[pu] <= depth[v] ? pu : v;
                while(aux != u)
                    ans[{aux, p[aux]}] = aq, aux = p[aux];
                u = depth[pu] <= depth[v] ? pu : v;
            }
            if(depth[v] > depth[pv]) {
                while(v != pv && v != u)
                    ans[{v, p[v]}] = aq, v = p[v];
            }
        }
    }
    for(int i = 1; i < n; i++) {
        auto [x, y] = edges[i];
        printf("%d\n", max(ans[{x, y}], ans[{y, x}]));
    }
}
