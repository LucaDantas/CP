#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 210, maxk = 1010, mod = 1000000007;

int dp[maxn][maxn][maxk];

int main() {
	int n, K; scanf("%d %d", &n, &K);
	vector<int> a(n);
	for(int& x : a)
		scanf("%d", &x);
	a.push_back(0);
	sort(a.begin(), a.end());

	for(int i = 0; i <= K; i++)
		dp[0][0][i] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= i; j++) {
			for(int k = 0; k <= K; k++) {
				int val = k + j * (a[i] - a[i-1]);
				if(val > K) continue;
				dp[i][j][val] += dp[i-1][j][k]; // Sozinho
				if(dp[i][j][val] >= mod) dp[i][j][val] -= mod;
				dp[i][j][val] += 1ll*dp[i-1][j][k]*j%mod; // Com um aberto
				dp[i][j+1][val] += dp[i-1][j][k]; // Abri
				dp[i][j-1][val] += 1ll*dp[i-1][j][k]*j%mod; // Fechei
				if(dp[i][j][val] >= mod) dp[i][j][val] -= mod;
				if(dp[i][j+1][val] >= mod) dp[i][j+1][val] -= mod;
				if(dp[i][j-1][val] >= mod) dp[i][j-1][val] -= mod;
			}
		}
	}

	printf("%d\n", dp[n][0][K]);
}