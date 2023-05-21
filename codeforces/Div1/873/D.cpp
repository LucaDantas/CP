#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(a) (a).begin(),(a).end()

constexpr int maxn = 1e6 + 10;

struct BIT {
    int bit[maxn];
    void upd(int x) {
        for(; x < maxn; x += x&-x)
            ++bit[x];
    }
    int query(int x) {
        int ans = 0;
        for(; x > 0; x -= x&-x)
            ans += bit[x];
        return ans;
    }
    int range(int l, int r) { return query(r) - (l ? query(l-1) : 0); }
    void clear(int n) { for(int i = 0; i <= 2*n+5; i++) bit[i] = 0; }
} bit;

int p[maxn];
int in[maxn], out[maxn], t;

vector<int> g[maxn];
vector<pair<int,int>> sorted_children[maxn];

void dfs(int u) { // nao precisa passar o pai porque a arvore eh dada rooted
    in[u] = ++t;
    for(int v : g[u])
        dfs(v), sorted_children[u].push_back({out[v], v});
    sort(all(sorted_children[u]));
    out[u] = ++t;
}

void clean(int n) {
    t = 0;
    bit.clear(n);
    for(int i = 0; i <= n; i++)
        g[i].clear(), sorted_children[i].clear(), in[i] = 0, out[i] = 0, p[i] = 0;
}

int get(int x) { return bit.range(in[x], out[x]); }

int main() {
    int test; scanf("%d", &test);
    while(test--) {
        int n; scanf("%d", &n);
        clean(n);
        for(int i = 2; i <= n; i++)
            scanf("%d", &p[i]), g[p[i]].push_back(i);
        dfs(1);
        int centroid = 1, filho = 0;
        bit.upd(in[1]);
        for(int i = 2; i <= n; i++) {
            int sz = i; // sz atual, so pra nao confundir
            bit.upd(in[i]);
            if(out[i] < in[centroid] || out[centroid] < in[i]) {
                if(2*get(centroid) <= sz)
                    filho = centroid, centroid = p[centroid];
            } else {
                int prox = lower_bound(all(sorted_children[centroid]), pair<int,int>(in[i], 0))->second; // achei o indice do filho
                if(2*get(prox) > sz) {
                    centroid = prox;
                    filho = g[centroid][0]; // it will always be better to choose the subtree looking to the parent, so it doesn't matter who the best child is
                } else if(get(prox) > get(filho)) {
                    filho = prox;
                }
            }
            int bom = max(sz - get(centroid), get(filho));
            printf("%d ", sz - 2*bom);
        }
        puts("");
    }
}
