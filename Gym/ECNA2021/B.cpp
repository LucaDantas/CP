#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010;

int a[maxn], p[maxn];

bool mark[maxn], culm[maxn];

int cost(int x) { return mark[x] ? 0 : (mark[x] = 1, cost(p[x]) + a[x]); }

int main() {
    memset(culm, 1, sizeof culm);
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    for(int i = 0, x, y; i < m; i++)
        scanf("%d %d", &x, &y), p[y] = x, culm[x] = 0;
    int ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++) if(culm[i]) {
        for(int j = 1; j <= n; j++) if(culm[j] && i != j) {
            memset(mark, 0, sizeof mark);
            mark[0] = 1;
            ans = min(ans, cost(i) + cost(j));
        }
    }
    printf("%d\n", ans);
}
