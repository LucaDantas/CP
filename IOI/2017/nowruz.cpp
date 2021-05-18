#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <queue>
#include <cstring>
#include <random>

#define maxn 1025

int n, m;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int k;
struct GERA
{
	FILE *result, *map_out;
	char map[maxn][maxn], sv[maxn][maxn];
	int mark[maxn][maxn], ans = 0;
	void limpa(int x, int y) {
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if(mark[nx][ny] != 2) {
					++mark[nx][ny];
					if(map[nx][ny] == '.' && mark[nx][ny] == 2)
						map[nx][ny] = 'X';
				}
			}
		}
	}

	struct PAR
	{
		int x, y;
	};

	void bfs(int sx, int sy) {
		mark[sx][sy] = 2; limpa(sx, sy);
		std::queue<PAR> q;
		q.push({sx, sy});
		while(q.size()) {
			int x = q.front().x, y = q.front().y; q.pop();
			int ok = 1;
			for(int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if(nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == '.' && mark[nx][ny] != 2) {
					ok = 0;
					mark[nx][ny] = 2;
					q.push({nx, ny}); limpa(nx, ny);
				}
			}
			ans += ok;
		}
	}

	void le() {
		scanf("%d %d %d", &n, &m, &k);
	
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				scanf(" %c", &sv[i][j]);
	}

	int gera(int x, int y) {
		memset(mark, 0, sizeof mark); ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				map[i][j] = sv[i][j];
		
		if(map[x][y] != '.') return -1;

		bfs(x, y);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(!mark[i][j] && map[i][j] == '.') map[i][j] = 'X';
		
		map_out = fopen("map.out", "w");
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++)
				fprintf(map_out, "%c", map[i][j]);
			fprintf(map_out, "\n");
		}
		fclose(map_out);

		result = fopen("result.out", "w");
		fprintf(result, "%d\n", ans);
		fclose(result);

		return ans;
	}
} gera;

std::mt19937 rng(std::random_device{}());

int rnd(int x) { return (int)(rng() % x + x) % x; }
int rnd(int l, int r) { return l + rnd(r-l+1); }

const int qtd = 100;

int main() {
	gera.le();
	int best = -1;
	for(int i = 0; i < qtd; i++) {
		int aq = gera.gera(rnd(n), rnd(m));
		if(aq <= best) continue;
		best = aq;
		system("cp map.out best.out & wait");
	}
	fprintf(stderr, "%d %d\n", best, k);
}