#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int a[maxn][maxn], dist[maxn][maxn][3];
int n, m;

void bfs(vector<pair<int,int>> s, int k) {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            dist[i][j][k] = 1000000;
    deque<pair<int,int>> q;
    for(auto [x, y] : s)
        dist[x][y][k] = 1, q.push_back({x, y});
    while(q.size()) {
        auto [x, y] = q.front(); q.pop_front();
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            int cost = (a[x][y] == a[nx][ny] ? 0 : (dx[i] == 1 && k) || (dx[i] == -1 && !k) ? 1 : 1000000);
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && dist[nx][ny][k] > dist[x][y][k] + cost) {
                dist[nx][ny][k] = dist[x][y][k] + cost;
                if(!cost) q.push_front({nx, ny});
                else q.push_back({nx, ny});
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    vector<pair<int,int>> start;
    for(int j = 1; j <= m; j++)
        start.push_back({n, j});
    bfs(start, 0);
    if(a[1][1] == a[1][m])
        return printf("%d\n", dist[1][1][0]), 0;
    bfs({{1, 1}}, 1);
    bfs({{1, m}}, 2);
    int ans = dist[1][1][0] + dist[1][m][0];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            // printf("%d | %d %d %d\n", a[i][j], dist[i][j][0], dist[i][j][1], dist[i][j][2]);
            ans = min(ans, dist[i][j][0] + dist[i][j][1] + dist[i][j][2] - 2);
    printf("%d\n", ans);
}