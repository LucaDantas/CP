#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

vector<int> g[maxn];

bool mark[maxn];

int sz = 0;

void dfs(int u) {
    sz++;
    mark[u] = 1;
    for(int v : g[u]) if(!mark[v])
        dfs(v);
}

int main() {
    int n, l, r; scanf("%d %d %d", &n, &l, &r);
    for(int i = 0, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
    int game = 0;
    for(int i = 1; i <= n; i++) if(!mark[i]) {
        sz = 0;
        dfs(i);
        if(sz >= l+r) continue; // it doesn't matter
        game ^= sz / l;
    }
    puts(game ? "Alice" : "Bob");
}
