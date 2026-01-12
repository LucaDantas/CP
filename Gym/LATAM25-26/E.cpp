#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

// prefix update +1, point set, global query
struct SegmentTree {
    int tree[1<<20], lazy[1<<20];
    SegmentTree() { build(1, 1, maxn); }
    void build(int node, int l, int r) {
        if(l == r)
            return (void)(tree[node] = l);

        int m = (l+r) >> 1;
        build(node << 1, l, m);
        build(node << 1|1, m+1, r);
        tree[node] = min(tree[node<<1], tree[node<<1|1]);
    }
    void apply(int node, int l, int r) {
        if(!lazy[node]) return;

        tree[node] += lazy[node];

        if(l != r) {
            lazy[node<<1] += lazy[node];
            lazy[node<<1|1] += lazy[node];
        }

        lazy[node] = 0;
    }

    // val is either +1 or -1
    void update_suf(int node, int l, int r, int pos, int val) {
        apply(node, l, r);

        if(pos <= l) {
            lazy[node] += val;
            apply(node, l, r);
            return;
        }
        if(r < pos)
            return;

        int m = (l + r) >> 1;
        update_suf(node<<1, l, m, pos, val);
        update_suf(node<<1|1, m+1, r, pos, val);
        tree[node] = min(tree[node<<1], tree[node<<1|1]);
    }

    int query() { return tree[1]; }
} seg;

int main() {
    int q; scanf("%d", &q);

    int active = 0;
    for(int i = 0; i < q; i++) {
        int val; scanf("%d\n", &val);

        int type = (val > 0) ? 1 : -1;
        active += type;

        if(abs(val) < maxn)
            seg.update_suf(1, 1, maxn, abs(val), -type);

        printf("%d%c", active + min(0, seg.query()), " \n"[i==q-1]);
    }
}
