#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int ans[maxn], p[7];

int main() {
    int n; scanf("%d", &n);
    p[0] = 1;
    for(int i = 1; i < 7; i++)
        p[i] = p[i-1] * 10;
    ans[0] = 0x3f3f3f3f;
    ans[1] = 1;
    for(int i = 2; i <= n; i++) {
        ans[i] = i;
        for(int j = 1; j <= i-j; j++)
            ans[i] = min(ans[i], ans[j] + ans[i-j]);
        for(int j = 2; j*j <= i; j++)
            if(!(i%j))
                ans[i] = min(ans[i], ans[j] + ans[i/j]);
        for(int j = 1; j < 7; j++) if((i%p[j])/p[j-1])
            ans[i] = min(ans[i], ans[i / p[j]] + ans[i % p[j]]);
    }
    printf("%d\n", ans[n]);
}