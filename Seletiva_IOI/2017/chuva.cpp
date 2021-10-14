#include <cstdio>
#include <cstring>

constexpr int maxn = 1001, maxk = 251; // fazendo pra N pequeno pq a memoria ta matadora

int n, m, k;

int col[maxn][maxn][maxk], a[maxn][maxn];

bool mark[maxn][maxn], mark2[maxn][maxn];

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

void junta(int p[], int q[]) { for(int i = 0; i < k; i++) p[i] |= q[i]; }

void dfs(int x, int y) {
	mark[x][y] = 1;
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(nx >= n || nx < 0 || ny >= m || ny < 0 || a[x][y] < a[nx][ny]) continue;
		if(!mark[nx][ny]) dfs(nx, ny);
		junta(col[x][y], col[nx][ny]);
	}
}

void dfs2(int x, int y) {
	mark2[x][y] = 1;
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(nx >= n || nx < 0 || ny >= m || ny < 0 || a[x][y] != a[nx][ny] || mark2[nx][ny]) continue;
		junta(col[nx][ny], col[x][y]);
		dfs2(nx, ny);
	}
}

int val(int x, int y, int K) { return (x < 0 || y < 0 ? 0 : col[x][y][K]); }
int get(int p, int t, int r, int s, int K) { return col[p][t][K] - val(p, s-1, K) - val(r-1, t, K) + val(r-1, s-1, K); }

int main() {
	scanf("%d %d %d", &n, &m, &k);
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
	
	for(int i = 0, x, y; i < k; i++)
		scanf("%d %d", &x, &y), --x, --y, col[x][y][i] = 1;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			dfs(i, j), dfs2(i, j);

	for(int i = 1; i < n; i++)
		for(int K = 0; K < k; K++)
			col[i][0][K] += col[i-1][0][K];
	
	for(int i = 1; i < m; i++)
		for(int K = 0; K < k; K++)
			col[0][i][K] += col[0][i-1][K];

	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++)
			for(int K = 0; K < k; K++)
				col[i][j][K] += col[i-1][j][K] + col[i][j-1][K] - col[i-1][j-1][K];

	int q; scanf("%d", &q);
	while(q--) {
		int p, t, r, s, ans = 0; scanf("%d %d %d %d", &p, &t, &r, &s);
		--p, --t, --r, --s;
		for(int K = 0; K < k; K++)
			ans += get(r, s, p, t, K) > 0;
		printf("%d\n", ans);
	}
}
