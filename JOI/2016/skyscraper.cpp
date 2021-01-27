#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 105, maxl = 1005, mod = 1000000007;

int dp[maxn][maxn][maxl][3];

// dp(i, j, k, z) | i == current position | j == number of components
// k == value of the permutation | z == number of ends filled

void add(int& a, long long b) {
	b %= mod;
	a += b;
	if(a >= mod) a -= mod;
}

int main() {
	int n, L; scanf("%d %d", &n, &L);

	vector<int> a(n);
	for(int& x : a)
		scanf("%d", &x);
	sort(a.begin(), a.end());
	
	if(n == 1) {puts("1"); return 0;}

	for(int i = 0; i <= L; i++)
		dp[0][0][i][0] = 1;

	for(int i = 0; i < n; i++) {
		int dif = a[i] - (i?a[i-1]:0);
		for(int j = 0; j <= i; j++) {
			for(int k = 0; k <= L; k++) {
				for(int z = 0; z <= min(j, 2); z++) {

					int val = k + dif * (2*j - z);

					if(val > L) continue;
					// Merge a component with one of the ends
					if(j && z != 2)
						add(dp[i+1][j][val][z+1], 1ll * dp[i][j][k][z] * (2-z));
					// Create a new component one of the ends
					if(z != 2)
						add(dp[i+1][j+1][val][z+1], 1ll * dp[i][j][k][z] * (2-z));
					// Merge two components in the middle
					if(j >= 2)
						add(dp[i+1][j-1][val][z], 1ll * dp[i][j][k][z] * (j-1));
					// Append to an existing component
					if(j)
						add(dp[i+1][j][val][z], 1ll * dp[i][j][k][z] * (2*j - z));
					// Create a new component in the middle
					add(dp[i+1][j+1][val][z], 1ll * dp[i][j][k][z] * (j+1-z));
				}
			}
		}
	}

	printf("%d\n", dp[n][1][L][2]);
}