#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010;

struct DSU {
    int pai[maxn];
    DSU() { iota(pai, pai+maxn, 0); }
    int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
    void join(int a, int b) { pai[find(b)] = find(a); }
};

bool mark[maxn];

int get(int x) { printf("? %d\n", x); fflush(stdout); int ans; scanf("%d", &ans); return ans; }

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        DSU dsu;
        memset(mark, 0, sizeof mark);

        int n; scanf("%d", &n);

        static vector<pair<int,int>> a; a.clear();
        for(int i = 1, x; i <= n; i++)
            scanf("%d", &x), a.push_back({x, i});
        sort(a.begin(), a.end(), greater<pair<int,int>>());

        for(auto [k, u] : a) {
            if(mark[u]) continue;
            mark[u] = 1;
            for(int i = 0; i < k; i++) {
                int v = get(u);
                dsu.join(u, v);
                if(mark[v]) break;
                mark[v] = 1;
            }
        }

        putchar('!');
        for(int i = 1; i <= n; i++)
            printf(" %d", dsu.find(i)); // o meu pai é minha cor
        puts("");
        fflush(stdout);
    }
}
