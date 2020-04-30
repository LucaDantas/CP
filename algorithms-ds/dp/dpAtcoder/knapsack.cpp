#include<bits/stdc++.h>
using namespace std;

#define MAXN 110
#define MAXC 100100

long long v[MAXN], w[MAXN], dp[MAXC][MAXN];
//The dimensions of the dp are dp[Weight carrying rn][Last item selected] It'll be in a way that we can only put items that come after the last one selected
//And the value of the dp will be the value that the knapsack is carrying

int main(){
    int n, c;
    long long ans = 0;
    cin >> n >> c;
    for(int i = 1; i <= n; i++){
        cin >> w[i] >> v[i];
    }
    for(int i = 1; i <= c; i++){
        for(int j = 1; j <= n; j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 1; i <= n; i++){
        dp[w[i]][i] = v[i];
    }
    for(int i = 1; i <= c; i++){
        for(int j = 1; j <= n; j++){
            if(dp[i][j] == -1) continue;
            ans = max(ans, dp[i][j]);
            for(int k = j+1; k <= n; k++){
                if(i + w[k] > c) continue;
                dp[w[k]+i][k] = max(dp[w[k]+i][k], dp[i][j] + v[k]);
            }
        }
    }
    cout << ans << endl;
}