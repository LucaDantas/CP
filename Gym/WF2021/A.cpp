#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1005;

int n, m, k;

char grid[maxn][maxn];

bool mark[maxn*maxn];

vector<int> g[maxn*maxn], rev[maxn*maxn];

int get(int x, int y) { if(x < 0 || y < 0 || x >= n || y >= m) return -1; return x*m + y; }
pair<int,int> back(int val) { return {val/m, val%m}; }

void dfs(int u) {
    mark[u] = 1;
    auto [x, y] = back(u);
    grid[x][y] = '#';
    for(int v : g[u])
        if(!mark[v])
            dfs(v);
}

int qtd[maxn*maxn];

set<int> merda;

void bfs() {
    queue<int> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int val = get(i, j);
            if(mark[val]) {
                qtd[val] = k;
                q.push(val);
            }
        }
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int v : rev[u]) {
            if(++qtd[v] == k && !merda.count(v)) {
                auto [x, y] = back(v);
                grid[x][y] = '#';
                q.push(v);
            }
        }
    }
}

int main() {
    memset(grid, '.', sizeof grid);
    scanf("%d %d %d", &m, &n, &k); // invertido de novo essa merda
    for(int K = 0; K < k; K++) {
        int dx, dy;
        scanf("%d %d", &dy, &dx);
        int b; scanf("%d", &b);
        set<int> corno;
        for(int i = 0, x, y; i < b; i++) {
            scanf("%d %d", &y, &x), --x, --y;
            grid[x][y] = '#';
            corno.insert(get(x, y));
            merda.insert(get(x-dx, y-dy));
        }
        auto add = [&](int x, int y) -> void {
            if(~y) {
                g[x].push_back(y);
                rev[y].push_back(x);
            }
        };
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(!corno.count(get(i, j)))
                    add(get(i, j), get(i-dx, j-dy));
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j] == '#' && !mark[get(i, j)])
                dfs(get(i, j));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%c", grid[i][j]);
        putchar('\n');
    }

    puts("");

    bfs();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%c", grid[i][j]);
        putchar('\n');
    }
}
