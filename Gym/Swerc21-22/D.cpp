#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int p[maxn];
long long x[maxn], d[maxn];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++)
        scanf("%d", p+i);
    for(int i = 1; i <= m; i++)
        scanf("%lld", x+i), x[i] <<= 1;
    sort(x+1, x+1+m);
    x[m+1] = inf;
    x[0] = -inf;
    for(int i = 0, ptr = 1; i < n; i++) {
        for(; x[ptr] < i*200; ptr++);
        d[i] = min(i*200 - x[ptr-1], x[ptr] - i*200);
    }
    long long ans = 0, now = 0;
    for(int i = 0, ptr = 0; i < n; i++) {
        int pos = i*200 + d[i] - 1; // tenho que estar o mais longe possivel mas ainda pegando
        for(; ptr < n && (abs(pos - ptr*200) < d[ptr] || i > ptr); now += p[ptr++]);
        ans = max(ans, now); // ptr nao ta incluido
        now -= p[i];
    }
    printf("%d\n", ans);
}
