#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

int a[maxn], ans[maxn], dp[maxn], pref[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    sort(a+1, a+1+n);
    for(int i = 1; i <= n; i++) {
        if(a[i] <= i)
            dp[i] = 1 + pref[i - a[i]];
        else
            dp[i] = i - a[i] + 1; // esqueci de colocar que isso formaria um grupo entao precisa adicionar 1
        pref[i] = max(pref[i-1], dp[i]);
    }
    for(int i = n, ptr = 1; i >= 1; i--)
        for(; ptr <= dp[i] + (n-i); ptr++)
            ans[ptr] = i;
    int q; scanf("%d", &q);
    while(q--) {
        int k; scanf("%d", &k);
        printf("%d\n", ans[k]);
    }
}
