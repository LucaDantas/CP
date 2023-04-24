#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e6+10, mod = 998244353;

int f[maxn], mi[maxn];

vector<int> pr;

void calc() {
    f[0] = f[1] = mi[1] = 1;
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) pr.push_back(i), f[i] = i, mi[i] = -1;
        for(int j = 0; pr[j] < f[i] && pr[j] * i < maxn; j++)
            f[i*pr[j]] = pr[j], mi[i*pr[j]] = -mi[i];
        if(1ll * i * f[i] < maxn)
            f[i * f[i]] = f[i], mi[i * f[i]] = 0;
    }
}

int power(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (int)(1ll * ans * b % mod);
        b = (int)(1ll * b * b % mod);
        e >>= 1;
    }
    return ans;
}

long long dp(int k, int m) { return power(2*k+1, m) - 1; } // (4k+i)^m-1, -1 pq eu tiro o caso tudo 0

int main() {
    calc();
    int m, k; scanf("%d %d", &m, &k);
    int ans = 1; // o caso 0,0,0,0,...
    for(int i = 1; i <= k; i++) {
        ans += dp(k/i, m) * mi[i];
        if(ans >= mod) ans -= mod;
        else if(ans < 0) ans += mod;
    }
    printf("%d\n", ans);
}
