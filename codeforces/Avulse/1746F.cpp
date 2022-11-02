#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

constexpr int maxn = 3e5+10, G = 30;

struct BIT {
    int bit[maxn];
    void upd(int x, int v) {
        for(x++; x < maxn; x += x&-x)
            bit[x] += v;
    }
    int query(int x) {
        int ans = 0;
        for(x++; x > 0; x -= x&-x)
            ans += bit[x];
        return ans;
    }
    int range(int l, int r) { return query(r) - query(l-1); }
} bit[G];

struct Query {
    int t, a, b, c;
} queries[maxn];

map<int, vector<int>> grp;

int main() {
    int n, q; scanf("%d %d", &n, &q);
    vector<int> a(n);
    for(int& x : a)
        scanf("%d", &x), grp[x];

    for(int i = 0; i < q; i++) {
        int t, a, b, c = 0; scanf("%d %d %d", &t, &a, &b);
        if(t == 2) scanf("%d", &c);
        else grp[b];
        queries[i] = {t, a, b, c};
    }

    for(auto& g : grp) {
        long long grps = rng();
        for(int b = 0; b < G; b++)
            if(grps & (1 << b))
                g.second.push_back(b);
    }
    
    for(int i = 0; i < n; i++)
        for(auto g : grp[a[i]])
            bit[g].upd(i, 1);

    for(int qq = 0; qq < q; qq++) {
        int t = queries[qq].t;
        if(t == 1) {
            int i = queries[qq].a, x = queries[qq].b;
            --i;
 
            for(int g : grp[a[i]])
                bit[g].upd(i, -1);

            a[i] = x;
            for(int g : grp[a[i]])
                bit[g].upd(i, 1);
        } else {
            auto [lixo, l, r, k] = queries[qq];
            --l, --r;
            bool ok = 1;
            for(int i = 0; i < G; i++)
                ok &= bit[i].range(l, r) % k == 0;
            puts(ok ? "YES" : "NO");
        }
    }
}
