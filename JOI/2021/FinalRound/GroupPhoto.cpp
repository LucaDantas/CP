#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e3+10;

bool mark[maxn];

int a[maxn], val[maxn][maxn], dp[maxn];

int main() {
	int n; scanf("%d", &n);
	int inv = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		for(int j = a[i]+1; j <= n; j++) {
			inv += mark[j];
			val[a[i]][j] += mark[j];
		}
		for(int j = a[i]-1; j >= 1; j--)
			val[j][a[i]] -= mark[j];
		mark[a[i]] = 1;
	}
	for(int sz = 2; sz <= n; sz++) {
		for(int i = 1; i+sz <= n; i++) {
			int j = i + sz;
			val[i][j] += val[i][j-1] + val[i+1][j] - val[i+1][j-1];
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			dp[i] = max(dp[i], val[j][i] + dp[j-1]);
	printf("%d\n", inv - dp[n]);
}