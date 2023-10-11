#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())

vector<vector<char>> a;
vector<vector<int>> dist[3];

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

bool valid(int x, int y) { return x >= 0 && x < sz(a) && y >= 0 && y < sz(a[0]); }

int val(int x, int y) { return a[x][y] == '.'; }

void bfs(int xs, int ys, int k) {
    deque<pair<int,int>> q;
    dist[k][xs][ys] = 0;
    q.push_front({xs, ys});
    while(q.size()) {
        auto [x, y] = q.front();
        q.pop_front();
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(valid(nx, ny) && dist[k][nx][ny] == 0x3f3f3f3f) {
                dist[k][nx][ny] = dist[k][x][y]+val(nx, ny);
                if(val(nx, ny))
                    q.push_back({nx, ny});
                else
                    q.push_front({nx, ny});
            }
        }
    }
}

int main() {
    int n, m; scanf("%d %d", &n, &m);
    a.assign(n, vector<char>(m));
    for(int k : {0, 1, 2})
        dist[k].assign(n, vector<int>(m, 0x3f3f3f3f));
    for(auto& linha : a)
        for(char& x : linha)
            scanf(" %c", &x);
    for(int i = 0, cnt = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '*')
                bfs(i, j, ++cnt);
            else if(a[i][j] == 'T')
                bfs(i, j, 0);
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            ans = min(ans, dist[0][i][j] + dist[1][i][j] + dist[2][i][j] - 2*val(i, j));
    printf("%d\n", ans);
}
