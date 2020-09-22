#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 2e3+10;
constexpr ll inf = 1e15L;

struct prob {
    int p, f, t; 
} a[maxn];

ll dp[maxn];

int main() {
    int n, T; scanf("%d %d", &n, &T);
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &a[i].p, &a[i].f, &a[i].t);
    }
    // a gente quer ordenar pelo que tem o menor F/T, então pra não usar double a gente compara
    // f_a*t_b > f_b*t_a
    sort(a, a+n, [](prob x, prob y){
       return 1ll * x.f * y.t > 1ll * y.f * x.t;
    });
    for(int i = 0; i < n; i++) {
        int p = a[i].p, f = a[i].f, t = a[i].t;
        for(int j = T-t; j >= 0; j--)
            dp[j+t] = max(dp[j+t], dp[j] + max(0ll, p - 1ll * (j+t) * f));
    }
    printf("%lld\n", *max_element(dp, dp+T+1));
}
