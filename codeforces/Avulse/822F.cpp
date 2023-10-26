#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

vector<pair<int,int>> g[maxn];
pair<int,int> edges[maxn]; // tenho que definir na dfs quem eh o pai dos dois
double comeco[maxn];

void dfs(int u, int p, double offset) {
    double add = 2.0/g[u].size();
    for(auto [v, id] : g[u]) if(v != p) {
        offset += add; // cara ta na proxima posicao
        if(offset >= 2) offset -= 2;
        edges[id] = {u, v};
        comeco[id] = offset;
        dfs(v, u, offset+1 - (offset+1 >= 2 ? 2 : 0));
    }
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), g[a].push_back({b, i}), g[b].push_back({a, i});
    dfs(1, 0, 0);
    printf("%d\n", n-1);
    for(int i = 1; i < n; i++) {
        printf("1 %d ", i);
        if(comeco[i] < 1)
            printf("%d %d %.8lf", edges[i].first, edges[i].second, comeco[i]);
        else
            printf("%d %d %.8lf", edges[i].second, edges[i].first, comeco[i]-1);
        puts("");
    }
}

