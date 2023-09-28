#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

map<int, int> mp;

vector<pair<int,int>> g[maxn];

int grau[maxn];

bool mark_edge[maxn];
bool mark[maxn];
bool cor[maxn];
vector<int> vis;

void dfs(int u) {
    vis.push_back(u);
    mark[u] = 1;
    while(g[u].size()) {
        auto [v, id] = g[u].back();
        g[u].pop_back();
        if(mark_edge[id]) continue;
        mark_edge[id] = 1;

        cor[id] = v>u;

        if(mark[v]) {
            while(vis.back() != v)
                vis.pop_back();
            return (void)(mark[u] = 0);
        } else {
            dfs(v);
            if(vis.back() != u)
                return (void)(mark[u] = 0);
        }
    }
    vis.pop_back();
}

int main() {
    int n; scanf("%d", &n);

    vector<array<int,3>> opa(n);

    int cnt = 0;
    for(auto &[l, r, id] : opa) {
        scanf("%d %d", &l, &r), ++r;
        id = ++cnt;
        mp[l] = mp[r] = 0;
    }

    cnt = 0;
    for(auto &it : mp)
        it.second = ++cnt;

    for(auto &[l, r, id] : opa) {
        l = mp[l], r = mp[r];

        g[l].push_back({r, id});
        g[r].push_back({l, id});
        grau[l]++, grau[r]++;
    }

    for(int i = 1, last = -1, sla = 1; i <= cnt; i++) {
        if((grau[i]&1)) {
            if(last != -1)
                g[i].push_back({last, n+sla}),
                g[last].push_back({i, n+sla}),
                ++sla,
                last = -1;
            else
                last = i;
        }
    }

    for(int i = 1; i <= cnt; i++)
        if(g[i].size()) dfs(i);

    for(int i = 1; i <= n; i++)
        printf("%d ", cor[i]);
    puts("");
}
