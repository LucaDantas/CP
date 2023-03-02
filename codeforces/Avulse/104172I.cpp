#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct BIT {
    int bit[maxn];
    void upd(int x, int v) {
        for(; x < maxn; x += x&-x)
            bit[x] += v;
    }
    int query(int x) {
        int ans = 0;
        for(; x > 0; x -= x&-x)
            ans += bit[x];
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l-1); // l is always at least one so it should be fine
    }
    void clear(int x) {
        for(; x < maxn; x += x&-x)
            bit[x] = 0;
    }
} bit;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);

        vector<int> a(n), b(m), pos(n+1), morreu(n+1, 1);

        bool ok = 1;

        int idx = 0;
        for(int& x : a)
            scanf("%d", &x), pos[x] = ++idx;
        for(int& x : b)
            scanf("%d", &x), morreu[x] = 0;

        vector<int> aux;
        for(int x : a)
            if(!morreu[x]) aux.push_back(x);

        ok = aux == b; // they must be in the same order

        multiset<int> opa, tool;
        opa.insert(0), opa.insert(n+1);

        for(int i = 0, x; i < k; i++)
            scanf("%d", &x), tool.insert(x);

        for(int val = n; val >= 1; val--) {
            if(!morreu[val]) opa.insert(pos[val]);
            else {
                auto it = opa.lower_bound(pos[val]);
                int l = *prev(it) + 1, r = *it - 1;
                int sz = r - l + 1 - bit.query(l, r);

                bit.upd(pos[val], 1);
                if(tool.size() > 0 && tool.upper_bound(sz) != tool.begin())
                    tool.erase(--tool.upper_bound(sz));
                else
                    ok = 0;
            }
        }

        puts(ok ? "YES" : "NO");

        for(int i = 1; i <= n; i++)
            bit.clear(i);
    }
}
