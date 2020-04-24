#include<bits/stdc++.h>
using namespace std;

long long dp[10010];
int op[] = {1,4,1};

int main(){
    int n;
    cin >> n;
    dp[0] = 1;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < 3; j++){
            if(i+j+1 <= n) dp[i+j+1] += dp[i]*op[j];
        }
    }
    cout << dp[n] << endl;
}