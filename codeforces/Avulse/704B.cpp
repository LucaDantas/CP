#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 5e3+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll x[maxn], cost[4][maxn];
ll dp[maxn][maxn];

inline void min_self(ll& a, ll b) {a = min(a, b);}

int main() {
	int n, s, e; scanf("%d %d %d", &n, &s, &e); --s, --e;
	for(int i = 0; i < n; i++)
		scanf("%lld", &x[i]);
	for(int k = 0; k < 4; k++)
		for(int i = 0; i < n; i++)
			scanf("%lld", &cost[k][i]);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			dp[i][j] = inf;

	dp[0][0] = 0;

	int k = 0, l = 0;
	for(int i = 0; i < n-1; i++) {
		for(int j = 0; j <= i; j++) {
			ll eu = dp[i][j];
			if(i == s) {
				k = 1;
				// Append to the beginning of some component
				if(j) min_self(dp[i+1][j-1], eu + x[i] + cost[2][i]);
				// Create a new component
				min_self(dp[i+1][j], eu - x[i] + cost[3][i]);
				continue;
			}
			if(i == e) {
				l = 1;
				// Append to the end of some component
				if(j) min_self(dp[i+1][j-1], eu + x[i] + cost[0][i]);
				// Create a new component
				min_self(dp[i+1][j], eu - x[i] + cost[1][i]);
				continue;
			}
			// Append to the end of some component
			if(j || k)
				min_self(dp[i+1][j], eu + cost[0][i] + cost[3][i]);
			// Append to the beginning of some component
			if(j || l)
				min_self(dp[i+1][j], eu + cost[1][i] + cost[2][i]);
			// Merge two components (one must be in the middle)
			if(j+k >= 2 || j+l >= 2)
				min_self(dp[i+1][j-1], eu + 2*x[i] + cost[0][i] + cost[2][i]);
			// Create a new component
			min_self(dp[i+1][j+1], eu - 2*x[i] + cost[1][i] + cost[3][i]);
		}
	}
	ll extra;
	if(s == n-1) extra = x[n-1] + cost[2][n-1];
	else if(e == n-1) extra = x[n-1] + cost[0][n-1];
	else extra = 2*x[n-1] + cost[0][n-1] + cost[2][n-1];
	printf("%lld\n", dp[n-1][0] + extra);
}