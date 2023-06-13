#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2010;

pair<int,int> itv[maxn];
int dp[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        memset(dp, 0, n*sizeof(int));
        for(int i = 0; i < n; i++)
            scanf("%d %d", &itv[i].first, &itv[i].second);
        sort(itv, itv+n);
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int r = 0x3f3f3f3f;
            for(int j = i+1; j < n && itv[j].first <= itv[i].second; j++)
                r = min(r, itv[j].second);
            r = max(r, itv[i].second);
            if(r == 0x3f3f3f3f) continue;
            ans = max(ans, dp[i]+1);
            for(int j = i+1; j < n; j++)
                if(itv[j].first > r)
                    dp[j] = max(dp[j], dp[i]+1);
        }
        printf("%d\n", n - ans*2);
    }
}
