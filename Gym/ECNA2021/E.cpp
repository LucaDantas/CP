#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 40;

int m;

struct Frac {
    long long p, q;
    Frac(long long _p = 0, long long _q = 1) { long long g = __gcd(_p, _q); p = _p/g, q = _q/g; }
    Frac operator*(const Frac& o) { return Frac(p * o.p, q * o.q); }
    Frac operator+(const Frac& o) { return Frac(p * o.q + o.p * q, q * o.q); }
};

bool mark[maxn][maxn];
Frac dp[maxn][maxn];

Frac solve(int n, int p, int used) {
    if(n == 0 && p == 0) return Frac(1, 1);
    if(n == 0 || p == 0 || 2*n > m || n > p) return Frac(0, 1);
    if(mark[n][p]) return dp[n][p];
    mark[n][p] = 1;
    dp[n][p] = Frac(2*n, m-used) * solve(n-1, p-1, used + 1) + Frac(m-used-2*n, m-used) * solve(n, p-1, used+1);
    return dp[n][p];
}

int main() {
    int n, p; scanf("%d %d %d", &m, &n, &p);
    Frac ans = solve(n, p, 0);
    printf("%lld/%lld\n", ans.p, ans.q);
}