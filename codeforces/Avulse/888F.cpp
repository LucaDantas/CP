#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 510, mod = 1000000007;

void add(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

int a[maxn][maxn], dp[maxn][maxn][2];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i < n; i++)
		a[n][i] = a[0][i], a[i][n] = a[i][0];
	for(int i = 0; i < n; i++)
		dp[i][i+1][0] = dp[i][i+1][1] = 1;
	for(int i = n-2; i >= 0; i--) {
		for(int j = i+2; j <= n; j++) {
			int& ans = dp[i][j][1];
			int& ans2 = dp[i][j][0];
			for(int x = i+1; x < j; x++) {
				if(a[i][x])
					add(ans, (int)(1ll * dp[i][x][1] * dp[x][j][1] % mod));
				if(a[x][j])
					add(ans2, (int)(1ll * dp[i][x][0] * dp[x][j][1] % mod)),
					add(ans, (int)(1ll * dp[i][x][0] * dp[x][j][1] % mod));
			}
		}
	}
	printf("%d\n", dp[0][n][0]);
}