#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e3+10;

int grid[maxn][maxn], v[maxn][maxn], h[maxn][maxn], n, m;
// 0 -> no one, 1 -> vertical, 2 -> horizontal
int dp[maxn][maxn][3];

inline int pos(int i, int j) { return m*i+j; }

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			char c; scanf(" %c", &c);
			grid[i][j] = (c=='R'?0:c=='G'?1:2);
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(i && i < n-1 && grid[i][j] == 1 && grid[i-1][j] == 0 && grid[i+1][j] == 2)
				v[i][j] = 1;
			if(j && j < m-1 && grid[i][j] == 1 && grid[i][j-1] == 0 && grid[i][j+1] == 2)
				h[i][j] = 1;
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(i>0 && j+1<m)
				for(int x : {0, 1, 2})
					dp[i][j][0] = max(dp[i][j][0], dp[i-1][j+1][x]);
			else
				dp[i][j][0] = 0;
			if(v[i][j]) {
				if(i>0 && j+1<m)
					for(int x : {0, 1})
						dp[i][j][1] = max(dp[i][j][1], dp[i-1][j+1][x]+1);
				else
					dp[i][j][1] = 1;
			}
			if(h[i][j]) {
				if(i>0 && j+1<m)
					for(int x : {0, 2})
						dp[i][j][2] = max(dp[i][j][2], dp[i-1][j+1][x]+1);
				else
					dp[i][j][2] = 1;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++) {
		int here = 0;
		for(int x : {0, 1, 2})
			here = max(here, dp[i][0][x]);
		ans += here;
	}
	for(int j = 1; j < m; j++) {
		int here = 0;
		for(int x : {0, 1, 2})
			here = max(here, dp[n-1][j][x]);
		ans += here;
	}
	printf("%d\n", ans);
}