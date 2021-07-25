#include <cstdio>

constexpr int maxn = 55, inf = 0x3f3f3f3f;

int dp[maxn][maxn][maxn];

int min(int a, int b) { return a < b ? a : b; }

int main() {
	for(int i = 1; i <= 30; i++) {
		for(int j = 1; j <= 30; j++) {
			for(int k = 1; k <= 50; k++) {
				if(k == i*j) dp[i][j][k] = 0;
				else dp[i][j][k] = inf;

				int& ans = dp[i][j][k];
				for(int pega = 1; pega <= k; pega++) {
					for(int qi = 1; qi < i; qi++)
						ans = min(ans, j*j + dp[qi][j][pega] + dp[i - qi][j][k - pega]);
					for(int qj = 1; qj < j; qj++)
						ans = min(ans, i*i + dp[i][qj][pega] + dp[i][j - qj][k - pega]);
				}
			}
		}
	}
	int t; scanf("%d", &t);
	while(t--) { int a, b, c; scanf("%d %d %d", &a, &b, &c); printf("%d\n", dp[a][b][c]); }
}
