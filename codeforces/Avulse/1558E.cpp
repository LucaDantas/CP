#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2010;

int n, m;

int a[maxn], b[maxn];

bool peguei[maxn];

int pai[maxn];

vector<int> g[maxn];

bool mark[maxn];

int bons;

void vapo(int u, int& val) {
    if(peguei[u]) return;
    ++bons;
    val += b[u];
    val = min(val, 0x3f3f3f3f);
    peguei[u] = 1;
    vapo(pai[u], val);
}

bool expand(int& val_base) {
    memset(mark, 0, sizeof mark);
    memset(pai, 0, sizeof pai);
    queue<pair<int,int>> q;
    for(int i = 1; i <= n; i++)
        if(peguei[i]) mark[i] = 1, q.push({i, val_base});

    while(q.size()) {
        auto [u, val_aq] = q.front(); q.pop();
        for(int v : g[u]) if(v != pai[u]) {
            if(!peguei[u] && mark[v]) {
                vapo(v, val_base); vapo(u, val_base);
                return 1;
            }
            if(!mark[v] && val_aq > a[v]) {
                mark[v] = 1;
                pai[v] = u;
                q.push({v, min(val_aq + b[v], 0x3f3f3f3f)});
            }
        }
    }
    return 0; // nao consegui expandir mais nada :(
}

bool check(int val) {
    memset(peguei, 0, sizeof peguei);
    peguei[1] = 1;
    bons = 1;
    while(expand(val));
    return bons == n;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(int i = 2; i <= n; i++)
            scanf("%d", a+i);
        for(int i = 2; i <= n; i++)
            scanf("%d", b+i);
        for(int i = 0, u, v; i < m; i++)
            scanf("%d %d", &u, &v), g[u].push_back(v), g[v].push_back(u);

        int l = 1, r = 0x3f3f3f3f, ans = -1;
        while(l <= r) {
            int mid = (l+r) >> 1;
            if(check(mid))
                ans = mid, r = mid-1;
            else
                l = mid+1;
        }
        
        printf("%d\n", ans);

        for(int i = 1; i <= n; i++)
            g[i].clear();
    }
}

