#include <stdio.h>
 
int min(int a, int b) { return a < b ? a : b; }
 
static int dp[510][510][11], dir[510][510], baixo[510][510];

int main() {
    int n, m, k; scanf("%d %d %d", &n, &m, &k);
    if(k&1) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                putchar('-'), putchar('1'), putchar(' ');
            putchar('\n');
        }
        return 0;
    }
    k >>= 1;
    const int inf = 0x3f3f3f3f;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m-1; j++)
            scanf("%d", &dir[i][j]);
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &baixo[i][j]);
    for(int rep = 1; rep <= k; rep++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                dp[i][j][rep] = inf;
                if(i) dp[i][j][rep] = min(dp[i][j][rep], dp[i-1][j][rep-1] + baixo[i-1][j]);
                if(i < n-1) dp[i][j][rep] = min(dp[i][j][rep], dp[i+1][j][rep-1] + baixo[i][j]);
                if(j) dp[i][j][rep] = min(dp[i][j][rep], dp[i][j-1][rep-1] + dir[i][j-1]);
                if(j < m-1) dp[i][j][rep] = min(dp[i][j][rep], dp[i][j+1][rep-1] + dir[i][j]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%d ", dp[i][j][k] << 1);
        puts("");
    }
}
