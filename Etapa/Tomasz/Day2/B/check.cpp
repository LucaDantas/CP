#include <cstdio>

constexpr int maxn = 102;

int dp[maxn][maxn];
char s[maxn][maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf(" %s", s[i]);
	dp[0][0] = s[0][0] == '.';
	for(int i = 1; i < n; i++) {
		if(s[0][i] == '.') dp[0][i] = dp[0][i-1];
		if(s[i][0] == '.') dp[i][0] = dp[i-1][0];
	}
	for(int i = 1; i < n; i++)
		for(int j = 1; j < n; j++)
			if(s[i][j] == '.') dp[i][j] = dp[i-1][j] + dp[i][j-1];
	printf("%d\n", dp[n-1][n-1]);
}