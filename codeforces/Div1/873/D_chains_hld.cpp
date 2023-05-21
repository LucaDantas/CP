#include <bits/stdc++.h>
using namespace std;

#define sz(a) ((int)(a).size())
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

int nxt[maxn], head[maxn], sz[maxn]; // pras chains do hld

pair<int,int> filho[maxn];

vector<int> g[maxn];
vector<pair<int,int>> sorted_children[maxn];

int get(int x) { return bit.range(in[x], out[x]); }

void dfs(int u) { // nao precisa passar o pai porque a arvore eh dada rooted
    in[u] = ++t;
    if(!head[u])
        head[u] = u;
    
    if(!sz(g[u]))
        return (void)(out[u] = ++t);

    for(int& v : g[u])
        if(sz[v] > sz[g[u].front()])
            swap(v, g[u].front());

    nxt[u] = g[u].front();
    head[g[u].front()] = head[u];
    for(int v : g[u])
        dfs(v), sorted_children[u].push_back({out[v], v});

    out[u] = ++t;
}

void insert(int u) {
    bit.upd(in[u]);
    while(head[u] != 1) {
        u = head[u];
        filho[p[u]] = max(filho[p[u]], {get(u), u});
        u = p[u];
    }
}

int get_filho(int u) { return max(get(nxt[u]), get(filho[u].second)); }

void clean(int n) {
    t = 0;
    bit.clear(n);
    for(int i = 0; i <= n; i++)
        g[i].clear(), sorted_children[i].clear(), filho[i] = {0,0}, sz[i] = 0, nxt[i] = 0, head[i] = 0, in[i] = 0, out[i] = 0, p[i] = 0;
}

int main() {
    int test; scanf("%d", &test);
    while(test--) {
        int n; scanf("%d", &n);
        clean(n);
        for(int i = 2; i <= n; i++)
            scanf("%d", &p[i]), g[p[i]].push_back(i);
        for(int i = n; i >= 1; i--)
            ++sz[i], sz[p[i]] += sz[i]; // mais facil de calcular os tamanhos assim
        dfs(1);
        int centroid = 1;
        bit.upd(in[1]);
        for(int i = 2; i <= n; i++) {
            int tam = i; // sz atual, so pra nao confundir
            insert(i);
            if(out[i] < in[centroid] || out[centroid] < in[i]) {
                if(2*get(centroid) <= tam)
                    centroid = p[centroid];
            } else {
                int prox = lower_bound(all(sorted_children[centroid]), pair<int,int>(in[i], 0))->second; // achei o indice do filho
                if(2*get(prox) > tam)
                    centroid = prox;
            }
            int bom = max(tam - get(centroid), get_filho(centroid));
            printf("%d ", tam - 2*bom);
        }
        puts("");
    }
}
