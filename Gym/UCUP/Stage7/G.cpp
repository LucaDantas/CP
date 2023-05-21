#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10, mod = 1e9+9;

int f[maxn], p[maxn];

void calc() {
    f[0] = 1, p[0] = 1;
    for(int i = 1; i < maxn; i++)
        f[i] = (int)(1ll * i * f[i-1] % mod), p[i] = 2 * p[i-1] % mod;
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

int main() {
    calc();
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n);
        long long sum = 0;
        for(int& x : a)
            scanf("%d", &x), sum += x;
        int val = (int)(2 * sum / n);
        sort(a.begin(), a.end());
        bool ok = 1; int diferentes = 0;
        for(int i = 0; i < (n+1)/2; i++)
            ok &= (a[i] + a[n-i-1]) == val, diferentes += a[i] != a[n-i-1];
        int permutacoes = f[n/2]; // primeiro coloco tudo e depois tenho que tirar as repetidas
        for(int i = 0; i < n/2; i++) {
            int grp = 1;
            for(; i+1 < n/2 && a[i+1] == a[i]; i++, grp++);
            permutacoes = (int)(1ll * permutacoes * power(f[grp], mod-2) % mod);
        }
        printf("%d\n", (int)(ok * (1ll * permutacoes * p[diferentes] % mod)));
    }
}
