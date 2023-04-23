#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 505*505*5 + 10;

vector<int> g[maxn], inv[maxn];

bool mark[maxn];

int n, m;

struct Pt {
    int i, j; char c;
} pts[505][505];

void add_inv(int a, int b) { inv[a].push_back(b), inv[b].push_back(a); }
void add_edge(int a, int b) { g[a].push_back(b), g[b].push_back(a); }

int get(Pt p, int pos) { return p.i * m * 4 + p.j*4 + pos; }
pair<int,int> back(int val) { return {val / (m*4), (val % (m*4)) / 4}; }

void add_inside(Pt p) {
    if(p.c == '.' || p.c == 'V' || p.c == 'H')
        add_edge(get(p, 0), get(p, 1)), add_edge(get(p, 2), get(p, 3));
    else if(p.c == '/')
        add_edge(get(p, 0), get(p, 2)), add_edge(get(p, 1), get(p, 3));
    else if(p.c == '\\')
        add_edge(get(p, 0), get(p, 3)), add_edge(get(p, 1), get(p, 2));

    if(p.c == 'V' || p.c == 'H')
        add_inv(get(p, 0), get(p, 2)); // todas as outras arestas ja sao determinadas por causa das arestas da mesma cor

}

void add_neighbour(Pt a, Pt b) {
    if(a.i == b.i) {
        if(a.j == b.j-1)
            add_edge(get(a, 3), get(b, 2));
        else
            add_edge(get(a, 2), get(b, 3));
    } else {
        if(a.i == b.i-1)
            add_edge(get(a, 1), get(b, 0));
        else
            add_edge(get(a, 0), get(b, 1));
    }
}

int cor[maxn], custo_cor[2];

void dfs(int u) {
    auto [i, j] = back(u);
    char c = pts[i][j].c;
    if(c == '#')
        custo_cor[(1+cor[u])/2] = maxn;
    if((c == 'V' && (u&2) == 2) || (c == 'H' && (u&2) == 0))
        ++custo_cor[(1+cor[u])/2]; // I have to turn the dude to make it work

    for(int v : g[u]) {
        if(!cor[v]) {
            cor[v] = cor[u];
            dfs(v);
        } else if(cor[v] != cor[u]) {
            printf("-1\n");
            exit(0);
        }
    }

    for(int v : inv[u]) {
        if(!cor[v]) {
            cor[v] = -cor[u];
            dfs(v);
        } else if(cor[v] == cor[u]) {
            printf("-1\n");
            exit(0);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; scanf(" %c", &c);
            pts[i][j] = {i, j, c};
            add_inside(pts[i][j]);
            if(i)
                add_neighbour(pts[i][j], pts[i-1][j]);
            if(j)
                add_neighbour(pts[i][j], pts[i][j-1]);
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            auto p = pts[i][j];
            // estado da gargula vertical eh 0, horizontal eh 1
            if(!cor[get(p, 0)] && (p.c == 'V' || p.c == 'H')) {
                custo_cor[0] = custo_cor[1] = 0;
                cor[get(p, 0)] = 1;
                dfs(get(p, 0));
                ans += min(custo_cor[0], custo_cor[1]);
            }
        }
    }
    printf("%d\n", ans >= maxn ? -1 : (ans >> 1));
}

