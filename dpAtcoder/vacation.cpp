#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100

int value[4][MAXN], dp[4][MAXN];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> value[1][i] >> value[2][i] >> value[3][i];
    }
    fill(dp[1], dp[1]+n+1, -1);
    fill(dp[2], dp[2]+n+1, -1);
    fill(dp[3], dp[3]+n+1, -1);
    dp[1][1] = 0;
    dp[2][1] = 0;
    dp[3][1] = 0;
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= 3; j++){
            for(int k = 1; k <= 3; k++){
                if(j == k) continue;
                dp[k][i+1] = max(dp[k][i+1], dp[j][i] + value[k][i]);
            }
        }
    }
    dp[1][n] += max(value[2][n], value[3][n]);
    dp[2][n] += max(value[1][n], value[3][n]);
    dp[3][n] += max(value[2][n], value[1][n]);
    cout << max(dp[1][n], max(dp[2][n], dp[3][n])) << endl;
}