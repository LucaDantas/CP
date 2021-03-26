// There are some problems that are simply 1e9 times easier to code
// recursively, I could not contain myself this time
#include<cstdio>
#include<cstring>

constexpr int maxn = 1e3+10, mod = 998244353;

char x[maxn], y[maxn];

int dp[maxn][maxn][3][4], n, m;

void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

int solve(int i, int j, int f, int teve, char last) {
	if(dp[i][j][f][teve] != -1) return dp[i][j][f][teve];
	int& here = dp[i][j][f][teve]; here = teve==3;
	if(i < n && x[i] != last) add(here, solve(i+1, j, 1, teve|1, x[i]));
	if(j < m && y[j] != last) add(here, solve(i, j+1, 2, teve|2, y[j]));
	return here;
}

int main() {
	scanf(" %s %s", x, y);
	n = (int)strlen(x), m = (int)strlen(y);
	int ans = 0;
	memset(dp, -1, sizeof dp);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			add(ans, solve(i, j, 0, 0, '*'));
	printf("%d\n", ans);
}