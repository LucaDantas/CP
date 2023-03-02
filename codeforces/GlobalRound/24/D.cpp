#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5010;

int f[maxn], inv[maxn], mod;

int power(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans = (int)(1ll * ans * b % mod);
        b = (int)(1ll * b * b % mod);
        e >>= 1;
    }
    return ans;
}

void calc() {
    f[0] = inv[0] = 1;
    for(int i = 1; i < maxn; i++)
        f[i] = (int)(1ll * f[i-1] * i % mod), inv[i] = power(f[i], mod-2);
}

int choose(int a, int b) {
    return (int)(1ll * f[a] * inv[b] % mod * inv[a-b] % mod);
}

int main() {
    int n; scanf("%d %d", &n, &mod);
    calc();
    int ans = 0;
    if(n&1) {
        for(int sz = 1; sz <= n/2; sz++) {
            for(int i = 0; i < sz; i++) {
                ans += (int)(1ll * choose(sz-1, i) * sz % mod * f[n-3-i] % mod);
                ans %= mod;
            }
        }
    } else {
        // adiciono manualmente o caso do diametralmente oposto
        ans += f[n-2]; ans %= mod;
        for(int sz = 1; sz < n/2; sz++) {
            // do outro lado eu posso escolher sz+1
            for(int i = 0; i < sz; i++) {
                ans += (int)(1ll * choose(sz-1, i) * (sz+1) % mod * f[n-3-i] % mod);
                ans %= mod;
            }
        }
    }
    printf("%d\n", (int)(1ll * ans * n % mod));
}
