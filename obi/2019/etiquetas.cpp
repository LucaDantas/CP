#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define endl '\n'

const int maxn = 1e4 + 100, inf = 1000000000;
int N, K, C, a[maxn], dp[maxn][maxn]; //dp[k][i]

int main(){
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> N >> K >> C;
	for(int i = 1; i <= N; i++)
		cin >> a[i];
	for(int k = 0; k <= K; k++)
		for(int i = 0; i <= N; i++)
			dp[k][i] = -inf;
	dp[0][0] = 0;
	for(int i = 1; i <= N; i++)
		dp[0][i] = dp[0][i-1] + a[i];
	for(int k = 1; k <= K; k++)
		for(int i = k*C; i <= N; i++)
			dp[k][i] = max(dp[k][i-1] + a[i], dp[k-1][i-C]);
	cout << dp[K][N] << endl;
}
