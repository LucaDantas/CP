#include <cstdio>

constexpr int maxn = 105;

double dp[maxn][maxn][maxn], ans;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
	int n; scanf("%d", &n);
	dp[n][n][0] = 1.0; // isso é a probabilidade
	for(int i = n; i >= 0; i--) {
		for(int j = n; j >= 0; j--) {
			for(int k = 0; k <= n; k++) {
				if(i) dp[i-1][j][max(k-1, 0)] += dp[i][j][k] * ((double)i / (i+j)); // jogar A
				if(j) dp[i][j-1][k+1] += dp[i][j][k] * ((double)j / (i+j)); // jogar B
			}
			if(i) ans += (dp[i][j][0] * i) * ((double)i / (i+j));
		}
	}
	printf("%lf\n", ans);
}
