#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

long long a[maxn];

struct SegmentTree {
    struct Node {
        long long ans[2][2];
        Node() { ans[0][0] = ans[0][1] = ans[1][0] = ans[1][1] = inf; }
        Node(long long val) { ans[0][0] = 0, ans[0][1] = ans[1][0] = inf, ans[1][1] = 2*val; } // 2* porque tem que passar dos dois lados
    } tree[4*maxn];
    Node comb(const Node& l, const Node& r) {
        Node ans = Node();
        for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++)
            ans.ans[i][j] = min({inf, l.ans[i][1] + r.ans[0][j], l.ans[i][0] + r.ans[1][j], l.ans[i][1] + r.ans[1][j]});
        return ans;
    }
    void build(int node, int i, int j) {
        if(i == j) return (void)(tree[node] = Node(a[i]));
        int m = (i+j) >> 1;
        build(node<<1, i, m);
        build(node<<1|1, m+1, j);
        tree[node] = comb(tree[node<<1], tree[node<<1|1]);
    }
    void upd(int node, int i, int j, int pos) {
        if(i == j) return (void)(tree[node] = Node(a[i]));
        int m = (i+j) >> 1;
        if(pos <= m)
            upd(node<<1, i, m, pos);
        else
            upd(node<<1|1, m+1, j, pos);
        tree[node] = comb(tree[node<<1], tree[node<<1|1]);
    }
    long long query() { return tree[1].ans[1][1]; }
} seg;

int main() {
    int n; scanf("%d", &n);
    --n;
    for(int i = 1; i <= n; i++)
        scanf("%lld", a+i);
    seg.build(1, 1, n);
    int q; scanf("%d", &q);
    while(q--) {
        int pos, val; scanf("%d %d", &pos, &val);
        a[pos] = val;
        seg.upd(1, 1, n, pos);
        printf("%lld\n", seg.query());
    }
}
