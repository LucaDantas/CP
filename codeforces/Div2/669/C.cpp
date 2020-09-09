#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+10;

int ans[maxn], now = 1;

int main() {
    int n; scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        printf("? %d %d\n", now, i); fflush(stdout);
        int a, b; scanf("%d", &a);
        printf("? %d %d\n", i, now); fflush(stdout);
        scanf("%d", &b);
        if(a > b) ans[now] = a, now = i;
        else ans[i] = b;
    }
    ans[now] = n;
    printf("!");
    for(int i = 1; i <= n; i++) printf(" %d", ans[i]);
    puts("");
}