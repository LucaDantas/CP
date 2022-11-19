#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e3+10, offset = 1e3+2;

struct DSU {
    struct SV {
        int a, b, bip;
    };

    vector<SV> sv;

    int pai[maxn], peso[maxn], c[maxn], bip = 1;

    DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; for(int i = 0; i < offset; i++) join(i, i+offset); }

    void clear(int n) { for(int i = 0; i <= n; i++) pai[i] = i, peso[i] = 1, c[i] = 0; bip = 1; sv.clear(); for(int i = 0; i <= n; i++) join(i, i+offset); }
    
    int find(int x, int& cor) { cor ^= c[x]; return pai[x] == x ? x : find(pai[x], cor); } 

    void join(int a, int b) {
        int ca = 0, cb = 0;
        a = find(a, ca), b = find(b, cb);

        if(peso[a] < peso[b])
            swap(a, b);
        sv.push_back({a, b, bip});

        if(a == b) {
            if(ca == cb) bip = 0;
            return;
        }

        pai[b] = a;
        peso[a] += peso[b];
        c[b] = ca^cb^1;
    }

    void rollback() {
        auto [a, b, last_bip] = sv.back(); sv.pop_back();
        if(a == b) bip = last_bip;
        else pai[b] = b, peso[a] -= peso[b];
    }

    bool create_edge(int a, int b, bool swp) {
        if(!swp)
            join(a+offset, b);
        else
            join(a, b);
        return bip;
    }
} dsu;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<vector<int>> a(n, vector<int>(n));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                if(a[i][j] == a[j][i]) continue;

                bool swp = a[i][j] > a[j][i];

                if(!dsu.create_edge(i, j, swp))
                    dsu.rollback(), swp ^= 1;
                if(swp)
                    swap(a[i][j], a[j][i]);
            }
        }

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                printf("%d%c", a[i][j], " \n"[j==n-1]);

        dsu.clear(n);
    }
}
