#include <stdio.h>

#define mod 998244353
#define maxn 200010

int f[maxn];

void calc() {
    f[0] = 1;
    for(int i = 1; i < maxn; i++)
        f[i] = (int)(1ll * f[i-1] * i % mod);
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

int choose(int a, int b) { return (int)(1ll * f[a] * power(f[b], mod-2) % mod * power(f[a-b], mod-2) % mod);  }

int val[maxn];

int qtd(int n, int k) {
    int ans = 0;
    for(int i = 0; i < k; i++)
        ans += 1ll * ((i&1) ? -1 : 1) * power(k-i, n) * choose(k, i) % mod,
            ans %= mod, ans += mod, ans %= mod;
    return ans;
}

int main() {
    calc();
    long long n, k; scanf("%lld %lld", &n, &k);
    if(n <= k) return puts("0"), 0;
    if(k)
        printf("%lld\n", 2ll * (qtd(n, n-k)) * choose(n, n-k) % mod);
    else
        printf("%d\n", f[n]);
}
