#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+20, offset = 50005, maxsz = 2023;

struct Box {
    int x1, y1, x2, y2, id;
    void read() { scanf("%d %d %d %d", &x1, &y1, &x2, &y2); }
    int intersect(const Box& o) {
        int dx = min(x2, o.x2) - max(x1, o.x1);
        int dy = min(y2, o.y2) - max(y1, o.y1);
        if(min(dx, dy) <= 0) return 0; // if they don't interesect
        return dx * dy;
    }
    int area() { return (x2-x1) * (y2-y1); }
    bool lower(const Box& o) { return o.y2 <= y1; } // o is lower than me
    bool upper(const Box& o) { return y2 <= o.y1; } // o is above me
    bool operator<(const Box& o) const { return y1 < o.y1; }
};

vector<Box> box[2][maxsz];

vector<int> g[maxn];

void add_edge(int a, int b) {
    g[a].push_back(b+offset);
    g[b+offset].push_back(a);
}

bool mark[maxn];
int match[maxn];

bool dfs(int u) {
    mark[u] = 1;

    if(u >= offset)
        return !match[u] || dfs(match[u]);
    
    for(int v : g[u])
        if(!mark[v] && dfs(v))
            return match[u] = v, match[v] = u, 1;

    return 0;
}

void clean() {
    memset(mark, 0, sizeof mark);
    memset(match, 0, sizeof match);
    for(int i = 0; i < maxn; i++)
        g[i].clear();
    for(int i = 0; i < maxsz; i++)
        box[0][i].clear(), box[1][i].clear();
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int m, n; // m is ground truth, n is detected
        scanf("%d %d", &m, &n); // it is read in this order m,n
        
        for(int i = 1; i <= m; i++) {
            Box b; b.read(); b.id = i;
            box[1][b.x1].push_back(b);
        }

        for(int i = 1; i <= n; i++) {
            Box b; b.read(); b.id = i;
            box[0][b.x1].push_back(b);
        }

        for(int i = 0; i < maxsz; i++)
            sort(box[0][i].begin(), box[0][i].end()), sort(box[1][i].begin(), box[1][i].end());

        for(int x_detect = 0; x_detect <= 2000; x_detect++) {
            for(int x_ground = max(0, x_detect-2); x_ground <= x_detect + 3; x_ground++) {
                for(int i = 0, ptr = 0; i < box[0][x_detect].size(); i++) {
                    for(; ptr < box[1][x_ground].size() && box[0][x_detect][i].lower(box[1][x_ground][ptr]); ptr++);

                    for(int j = ptr; j < box[1][x_ground].size() && !box[0][x_detect][i].upper(box[1][x_ground][j]); j++)
                        if(box[0][x_detect][i].intersect(box[1][x_ground][j])*2 >= box[1][x_ground][j].area())
                            add_edge(box[0][x_detect][i].id, box[1][x_ground][j].id);
                }
            }
        }

        int ans = 0, last = -1;
        while(ans != last) {
            last = ans;
            memset(mark, 0, sizeof mark);
            for(int i = 1; i <= n; i++)
                if(!mark[i] && !match[i]) ans += dfs(i);
        }

        printf("%d\n", ans);

        clean();
    }
}
