#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1<<18;

int a[maxn];

struct SegmentTree {
    struct Node {
        int mx, mn;
        Node() : mx(-maxn), mn(maxn) {} // trash
        Node(int i, int val) : mx(i + val), mn(i - val) {}
    } tree[maxn<<1];
    Node& comb(const Node& l, const Node& r) {
        static Node ans;
        ans.mx = max(l.mx, r.mx);
        ans.mn = min(l.mn, r.mn);
        return ans;
    }
    void build(int node, int i, int j) {
        if(i == j) return (void)(tree[node] = Node(i, a[i]));
        int m = (i+j) >> 1;
        build(node<<1, i, m);
        build(node<<1|1, m+1, j);
        tree[node] = comb(tree[node<<1], tree[node<<1|1]);
    }
    void rm(int node, int i, int j, int pos) {
        if(i == j) return (void)(tree[node] = Node());
        int m = (i+j) >> 1;
        if(pos <= m)
            rm(node<<1, i, m, pos);
        else
            rm(node<<1|1, m+1, j, pos);
        tree[node] = comb(tree[node<<1], tree[node<<1|1]);
    }
    int get_mn(int node, int i, int j, int l, int r, int val) {
        if(i > r || j < l || tree[node].mn > val) return -1;
        if(i == j) return i;
        int m = (i+j) >> 1;
        int ans = get_mn(node<<1, i, m, l, r, val);
        if(ans == -1)
            return get_mn(node<<1|1, m+1, j, l, r, val);
        return ans;
    }
    int get_mx(int node, int i, int j, int l, int r, int val) {
        if(i > r || j < l || tree[node].mx < val) return -1;
        if(i == j) return i;
        int m = (i+j) >> 1;
        int ans = get_mx(node<<1, i, m, l, r, val);
        if(ans == -1)
            return get_mx(node<<1|1, m+1, j, l, r, val);
        return ans;
    }
} seg;

int dist[maxn];

void bfs(int s, int n) {
    for(int i = 1; i <= n; i++)
        dist[i] = maxn;
    dist[s] = 0; seg.rm(1, 1, n, s);
    queue<int> q; q.push(s);
    while(q.size()) {
        int i = q.front(); q.pop();
        {
            int v = seg.get_mx(1, 1, n, i-a[i], i, i);
            while(v != -1) {
                q.push(v); dist[v] = dist[i] + 1;
                seg.rm(1, 1, n, v);
                v = seg.get_mx(1, 1, n, i-a[i], i, i);
            }
        }
        {
            int v = seg.get_mn(1, 1, n, i, i+a[i], i);
            while(v != -1) {
                q.push(v); dist[v] = dist[i] + 1;
                seg.rm(1, 1, n, v);
                v = seg.get_mn(1, 1, n, i, i+a[i], i);
            }
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, x, y; scanf("%d %d %d", &n, &x, &y);
        for(int i = 1; i <= n; i++)
            scanf("%d", a+i);
        seg.build(1, 1, n);
        bfs(x, n);
        printf("%d\n", dist[y]);
    }
}
