#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1<<18;

struct SegmentTree {
    struct Node {
        int total, mspos, msneg;
        bool sz; // only matters if it's even or odd
        void set(int x) { if(x) total = x, mspos = x, msneg = -maxn, sz = 1; }
        void kill() { total = sz = 0, mspos = msneg = -maxn; }
    } tree[maxn<<1];
    int a[maxn];
    Node merge(const Node& l, const Node& r) {
        Node ans;
        ans.sz = l.sz^r.sz;
        if(l.sz) {
            // odd
            ans.total = l.total - r.total;
            ans.mspos = max(l.mspos - 2*r.total, r.msneg);
            ans.msneg = max(l.msneg + 2*r.total, r.mspos);
        } else {
            // even
            ans.total = l.total + r.total;
            ans.mspos = max(l.mspos + 2*r.total, r.mspos);
            ans.msneg = max(l.msneg - 2*r.total, r.msneg);
        }
        // 2* nesses cara tudo porque eu nao so quero apagar eles mas quero inverter de sinal
        return ans;
    }
    void build(int node, int i, int j) {
        if(i == j) return (void)(tree[node].set(a[i]));
        int m = (i+j) >> 1;
        build(node<<1, i, m), build(node<<1|1, m+1, j);
        tree[node] = merge(tree[node<<1], tree[node<<1|1]);
    }
    void upd(int node, int i, int j, int x) {
        if(i == j) return (void)(tree[node].kill());
        int m = (i+j)>>1;
        if(x <= m) upd(node<<1, i, m, x);
        else upd(node<<1|1, m+1, j, x);
        tree[node] = merge(tree[node<<1], tree[node<<1|1]);
    }
    int get() { return tree[1].total - (tree[1].sz ? tree[1].mspos : 0); }
} seg;

int main() {
    int n, q; scanf("%d %d", &n, &q);

    vector<int> a(n), upd(q);
    for(int& x : a)
        scanf("%d", &x);
    for(int& x : upd)
        scanf("%d", &x), a.push_back(x);

    sort(a.begin(), a.end(), greater<int>());

    for(int x : a)
        seg.a[n+q-x+1] = x;

    seg.build(1, 1, n+q);

    vector<int> ans;
    reverse(upd.begin(), upd.end());
    for(int x : upd) {
        ans.push_back(seg.get());
        seg.upd(1, 1, n+q, n+q-x+1);
    }
    ans.push_back(seg.get());
    reverse(ans.begin(), ans.end());
    for(int x : ans)
        printf("%d\n", x);
}
