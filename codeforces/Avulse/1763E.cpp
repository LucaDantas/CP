#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int dp[maxn];

int choose(int x) { return x * (x-1) / 2; }

int main() {
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    int p; scanf("%d", &p);
    for(int tam = 1; tam <= p; tam++) {
        for(int i = 700; i >= 2; i--)
            if(choose(i) <= tam)
                dp[tam] = min(dp[tam], dp[tam-choose(i)] + i);
    }
    printf("%d %d\n", dp[p], choose(dp[p]) - p);
}
