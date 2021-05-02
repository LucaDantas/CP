#include <stdio.h>

constexpr int maxn = 33;

long long choose[maxn][maxn], dp[maxn*maxn][2*maxn][2*maxn];

int sum(int a) { return a * (a - 1) / 2; }

int main() {
	int n, K; scanf("%d %d", &n, &K);
	
	choose[0][0] = 1;
	for(int a = 1; a < maxn; a++)
		for(int b = 0; b <= a; b++)
			choose[a][b] = choose[a-1][b] + (b?choose[a-1][b-1]:0);


	for(int i = 1; i <= n+1 && sum(i) <= K; i++)
		dp[sum(i)][i][i-1] = 1;

	for(int k = 0; k <= K; k++) {
		for(int sz = 1; sz <= 2*n+1; sz++) {
			for(int b = 0; b <= n+1; b++) {
				if(!dp[k][sz][b]) continue;
				for(int x = b + 2; x + sz <= 2*n+1 && k+sum(x) <= K; x++)
					dp[k+sum(x)][sz + x][x - b - 2] += dp[k][sz][b] * choose[x-1][b+1];
			}
		}
	}

	long long answer = dp[K][2 * n + 1][0];
	for(int i = 0; i <= 2 * n + 1; i++)
		for(int j = 0; j <= K; j++)
			for(int k = 1; k <= n; k++)
				answer += dp[j][i][k] * dp[K - j][(2 * n + 1) - i][k - 1];
	printf("%lld\n", answer);
}