#include <stdio.h>

#define maxn 100010

int p[maxn], diam[maxn], ans[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 2; i <= n; i++)
        scanf("%d", p+i);
    for(int i = n; i >= 1; i--) {
        diam[i] = diam[i] > 1 ? diam[i] : 1;
        ans[i] = ans[i] > diam[i] ? ans[i] : diam[i];
        diam[p[i]] = diam[p[i]] > diam[i] + 1 ? diam[p[i]] : diam[i] + 1;
        ans[p[i]] += ans[i];
    }
    printf("%d\n", ans[1]);
}
