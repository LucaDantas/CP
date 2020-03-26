#include<bits/stdc++.h>
using namespace std;

#define INF 2000000000
#define MAXN 100100

int dp[MAXN], h[MAXN];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> h[i];
    }
    fill(dp, dp+n+1, INF);
    dp[1] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 2; j++){
            if(i-j < 1) continue;
            dp[i] = min(dp[i], dp[i-j] + abs(h[i] - h[i-j]));
        }
    }
    cout << dp[n] << endl;
}