#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 510;

int dp[maxn][maxn], new_dp[maxn][maxn];

int a[maxn], b[maxn], m1, m2;

int main() {
	int n; scanf("%d", &n);
	scanf("%d", &m1);
	for(int i = 0; i < m1; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m2);
	for(int i = 0; i < m2; i++)
		scanf("%d", &b[i]);
	for(int i = 0; i <= m1; i++)
		for(int j = 0; j <= m2; j++)
			dp[i][j] = new_dp[i][j] = -inf;
	dp[0][0] = 0;
	for(int col = 0; col < n; col++) {
		for(int i = 0; i <= m1; i++) {
			for(int j = 0; j <= m2; j++) {
				if(i < m1)
					new_dp[i+1][j] = max(new_dp[i+1][j], dp[i][j]);
				if(j < m2)
					new_dp[i][j+1] = max(new_dp[i][j+1], dp[i][j]);
				if(i < m1 && j < m2)
					new_dp[i+1][j+1] = max(new_dp[i+1][j+1], dp[i][j]+a[i]*b[j]);
			}
		}
		for(int i = 0; i <= m1; i++) {
			for(int j = 0; j <= m2; j++) {
				dp[i][j] = max(dp[i][j], new_dp[i][j]);
			}
		}
	}
	printf("%d\n", dp[m1][m2]);
}
