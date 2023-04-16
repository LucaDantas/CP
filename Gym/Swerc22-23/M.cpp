#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct SegmentTree {
    int n = maxn;
    int tree[2*maxn + 100];
    void upd(int p, int v) {
        for(tree[p += n] = v; p > 0; p >>= 1)
            tree[p>>1] = max(tree[p], tree[p^1]);
    }
    // query the segment [l..r]
    int query(int l, int r) {
        ++r;
        int ans = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans = max(ans, tree[l++]);
            if(r&1) ans = max(ans, tree[--r]);
        }
        return ans;
    }
} seg;

vector<int> g[maxn];

int c[maxn], in[maxn], out[maxn], p[maxn], t, ans;

void dfs(int u) {
    in[u] = ++t;
    if(c[u]) ans = max(ans, u);
    else seg.upd(in[u], u);
    for(int v : g[u]) if(v != p[u])
        c[v] = 1^c[u], p[v] = u, dfs(v);
    out[u] = ++t;
}

int main() {
    int n; scanf("%d", &n);
    if(!(n&1)) return (printf("%d\n", n), 0);
    for(int i = 1, u, v; i < n; i++)
        scanf("%d %d", &u, &v), g[u].push_back(v), g[v].push_back(u);
    dfs(n);
    for(int i = 1; i <= n; i++)
        if(g[i].size() == 1) ans = max(ans, i);
    for(int u = 1; u <= n; u++) if(!c[u]) {
        vector<int> opa;
        int val = max(seg.query(1, in[u]-1), seg.query(out[u]+1, maxn-1));
        opa.push_back(val);

        for(int v : g[u]) if(v != p[u])
            opa.push_back(seg.query(in[v], out[v]));

        sort(opa.begin(), opa.end(), greater<int>());
        opa.push_back(0), opa.push_back(0);
        ans = max(ans, opa[2]); // terceira maior subarvore
    }
    printf("%d\n", ans);
}
