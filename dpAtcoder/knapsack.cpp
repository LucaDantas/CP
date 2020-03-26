#include<bits/stdc++.h>
using namespace std;

#define MAXN 110
#define MAXW 100100

int v[MAXN], w[MAXN], dp[MAXW][MAXN];
//The dimensions of the dp are dp[Weight carrying rn][Last item selected] It'll be in a way that we can only put items that come after the last one selected
//And the value of the dp will be the value that the knapsack is carrying

int main(){
    int n, c;
    cin >> n >> c;
    for(int i = 1; i <= n; i++){
        cin >> w[i] >> v[i];
    }
    for(int i = 1; i <= w; i++){
        for(int j = 1; j <= n; j++){
            dp[i][j] = 0;
        }
    }

}