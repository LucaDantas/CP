#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define pii pair<int, int>

vector<pii> v;
int dp[MAXN][MAXN];
//The dp works like dp[Number of boxes already used][last element used]

int main(){
    int n, ans = -1;
    scanf("%d", &n);
    for(int i = 0, p, r; i < n; i++){
        scanf("%d%d", &p, &r);
        v.push_back(make_pair(-r, p));
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++){
        int r = -v[i].first - v[i].second;
        if(r < 0) continue;
        ans = 0;
        dp[0][i] = r;
    }
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(dp[i][j] == -1) continue;
            ans = i;
            for(int k = j+1, r; k < n; k++){
                r = min(dp[i][j], -v[k].first) - v[k].second;
                if(r < 0) continue;
                dp[i+1][k] = max(dp[i+1][k], r);
            }
        }
    }
    printf("%d\n", ans+1);
}