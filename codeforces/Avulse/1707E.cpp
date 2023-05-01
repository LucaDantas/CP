#include <bits/stdc++.h>
using namespace std;

// I assume the answer is always achievable in at most 2^30 operations
constexpr int maxn = 1e5+10, maxk = 30, inf = 0x3f3f3f3f;

// nao precisa de update porque eu vou sempre so dar build uma camada por camada
struct SegmentTree {
    struct Node {
        int l, r;
        Node(int _l = inf, int _r = -inf) : l(_l), r(_r) {}
    } tree[maxn<<1];

    Node comb(const Node& a, const Node& b) { return Node(min(a.l, b.l), max(a.r, b.r)); }

    void set(int x, int l, int r) { tree[x + maxn] = Node(l, r); }
    Node get(int x) { return tree[x + maxn]; }

    void build() {
        for(int i = maxn-1; i > 0; i--)
            tree[i] = comb(tree[i<<1], tree[i<<1|1]);
    }

    // query the segment [l, r) -- intended, since the interval at i is actually the answer of [i,i+1]
    Node query(int l, int r) {
        Node ansl, ansr;
        for(l += maxn, r += maxn; l < r; l >>= 1, r >>= 1) {
            if(l&1) ansl = comb(ansl, tree[l++]);
            if(r&1) ansr = comb(tree[--r], ansr);
        }
        return comb(ansl, ansr);
    }
} seg[maxk];

int a[maxn];

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 0; i < n; i++)
        scanf("%d", a+i), --a[i];
    for(int i = 0; i+1 < n; i++)
        seg[0].set(i, min(a[i], a[i+1]), max(a[i], a[i+1]));
    seg[0].build();

    for(int k = 1; k < maxk; k++) {
        for(int i = 0; i+1 < n; i++) {
            auto [nowl, nowr] = seg[k-1].get(i); // get the value at this position, not a query
            auto [l, r] = seg[k-1].query(nowl, nowr); // onde o meu intervalo k-1 aponta
            seg[k].set(i, l, r);
        }
        seg[k].build();
    }

    while(q--) {
        int l, r; scanf("%d %d", &l, &r); --l, --r;
        if(l == 0 && r == n-1) { puts("0"); continue; }
        if(l == r) { puts("-1"); continue; }
        int ans = 0;
        for(int k = maxk-1; k >= 0; k--) {
            auto [ql, qr] = seg[k].query(l, r);
            if(ql > 0 || qr < n-1)
                ans += 1<<k, l = ql, r = qr;
        }
        auto [ql, qr] = seg[0].query(l, r);
        if(ql == 0 && qr == n-1)
            printf("%d\n", ans+1);
        else
            puts("-1");
    }
}
