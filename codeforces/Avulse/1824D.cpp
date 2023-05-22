#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())

constexpr int maxn = 1<<20;

using ll = long long;

int n;

struct SegmentTree {
    struct Node {
        ll val, sum, lazy_sum;
        int lazy_val, last_t, lazy_t;
        Node(ll _val = 0, ll _sum = 0, int _last_t = 0) : val(_val), sum(_sum), lazy_sum(0), lazy_val(0), last_t(_last_t), lazy_t(0) {}
        void convert_lazy(int t) {
            lazy_sum += 1ll * lazy_val * (t - lazy_t);
            lazy_t = t;
        }
        void apply_lazy(int sz) {
            if(!lazy_t) return;

            sum += lazy_sum * sz + val * (lazy_t - last_t);
            val += 1ll * lazy_val * sz; // o ultimo valor da lazy so eh passado como lazy_sum, nao como valor agora
            last_t = lazy_t;

            lazy_sum = lazy_val = lazy_t = 0;
        }
        void set_lazy(int t, int v) {
            // this will overwrite whatever is in it, so it should be pushed before
            lazy_val = v;
            lazy_t = t;
        }

        ll eval(int t) const { // needs to have been pushed already
            return sum + val * (t - last_t);
        }
    } tree[maxn<<1];

    int time;

    Node combine(const Node& l, const Node& r) { return Node(l.val + r.val, l.eval(time) + r.eval(time), time); }

    void push(int node, int l, int r) {
        if(!tree[node].lazy_t) return;
        if(l != r) for(int child : {node<<1, node<<1|1}) {
            tree[child].convert_lazy(tree[node].lazy_t);
            tree[child].lazy_val += tree[node].lazy_val;
            tree[child].lazy_sum += tree[node].lazy_sum;
        }
        tree[node].apply_lazy(r-l+1);
    }

    void upd(const int& node, const int& i, const int& j, const int& l, const int& r, const int& val) {
        push(node, i, j);
        if(i > r || j < l) return;
        if(i >= l && j <= r) return (void)(tree[node].set_lazy(time, val), push(node, i, j));
        int m = (i+j)>>1;
        upd(node<<1, i, m, l, r, val);
        upd(node<<1|1, m+1, j, l, r, val);
        tree[node] = combine(tree[node<<1], tree[node<<1|1]);
    }
    void upd(int l, int r, int val) {
        upd(1, 1, n, l, r, val);
    }

    Node query(const int& node, const int& i, const int& j, const int& l, const int& r) {
        push(node, i, j);
        if(i > r || j < l) return Node();
        if(i >= l && j <= r) return tree[node];
        int m = (i+j)>>1;
        return combine(query(node<<1, i, m, l, r), query(node<<1|1, m+1, j, l, r));
    }
    ll query(int l, int r) {
        return query(1, 1, n, l, r).eval(time+1); // time+1 porque eu quero contar o tempo atual na resposta, que normalmente nao ta incluido
    }

    void tick() { ++time; }
};

struct ST {
    SegmentTree seg;
    set<int> ativos;
    ST() { ativos.insert(0); } // precisa sempre existir um prev(it)
    void add(int x) { ativos.insert(x); seg.upd(x, x, x); }
    void rm(int x) {
        auto it = ativos.find(x);
        seg.upd(*prev(it)+1, x, *next(it) - x); // mudo o valor dos caras no meu intervalo de x pro proximo indice
        ativos.erase(it);
    }
    ll query(int l, int r) { return seg.query(l, r); }
} st;

ll ans[maxn];

struct Query {
    int x, l, r, id, sign;
    bool operator<(const Query& o) const { return x < o.x; }
};

int a[maxn];
int last[maxn];

int main() {
    int q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    vector<Query> qr;
    for(int i = 1; i <= q; i++) {
        int l1, r1, l2, r2; scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        qr.push_back({l2-1, l1, r1, i, -1});
        qr.push_back({r2, l1, r1, i, 1});
    }
    sort(qr.begin(), qr.end());
    int ptr = 0;
    for(int i = 1; i <= n; i++) {
        for(; ptr < sz(qr) && qr[ptr].x < i; ptr++)
            ans[qr[ptr].id] += qr[ptr].sign * st.query(qr[ptr].l, qr[ptr].r);
        st.seg.tick();
        st.add(i);
        if(last[a[i]])
            st.rm(last[a[i]]);
        last[a[i]] = i;
    }
    for(; ptr < sz(qr); ptr++)
        ans[qr[ptr].id] += qr[ptr].sign * st.query(qr[ptr].l, qr[ptr].r);
    for(int i = 1; i <= q; i++)
        printf("%lld ", ans[i]);
    puts("");
}
