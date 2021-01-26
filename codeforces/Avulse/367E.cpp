#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 350, mod = 1000000007;

int dp[2][maxn][maxn];

int fat(int m) {
	int ans = 1;
	for(int i = 1; i <= m; i++)
		ans = (int)(1ll*ans*i%mod);
	return ans;
}

void add(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

int main() {
	int n, m, x; scanf("%d %d %d", &n, &m, &x); swap(n, m);
	if(m > n) {puts("0"); return 0;}
	dp[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= min(i, m); j++) {
			for(int k = 0; k <= j; k++) {
				if(j < m)
					add(dp[1][j+1][k+1], dp[0][j][k]); // Abrir
				add(dp[1][j+1][k], dp[0][j][k]); // Abrir e fechar
				if(x != i)
					add(dp[1][j][k], dp[0][j][k]); // Fazer nd
				if(k && x != i)
					add(dp[1][j][k-1], dp[0][j][k]); // Fechar
			}
		}
		for(int j = 0; j <= min(i, m); j++)
			for(int k = 0; k <= j; k++)
				dp[0][j][k] = dp[1][j][k], dp[1][j][k] = 0;
	}
	printf("%d\n", (int)(1ll*dp[0][m][0]*fat(m)%mod));
}