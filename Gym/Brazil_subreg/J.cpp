#include <bits/stdc++.h>
using namespace std;

int cnt[14];

int main() {
    int n; scanf("%d", &n);
    int a, b;
    scanf("%d %d", &a, &b); a = min(a, 10), b = min(b, 10);
    int lx = a+b; cnt[a]++, cnt[b]++;
    scanf("%d %d", &a, &b); a = min(a, 10), b = min(b, 10);
    int s = a+b; cnt[a]++, cnt[b]++;
    for(int i = 0, x; i < n; i++)
        scanf("%d", &x), x = min(x, 10), s += x, lx += x, cnt[x]++;
    int r = 23 - s, l = min(r, 24-lx);
    if(l > 10) return (puts("-1"), 0);
    for(int i = l; i <= r; i++)
        if(cnt[i] < 4) return (printf("%d\n", min(10, i)), 0);
    puts("-1");
}
