#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<long long> a(n);
        pair<long long,int> mn = {0,n};

        for(int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            a[i] += (i ? a[i-1] : 0);
            mn = min(mn, {a[i], i});
        }

        vector<int> pot(n+1);
        pot[0] = 1;
        for(int i = 1; i <= n; i++)
            pot[i] = (pot[i-1]<<1)%mod;


        if(!mn.first) {
            printf("%d\n", pot[n]);
            continue;
        }

        vector<int> maiores_pre(n); // nao inclui si mesmo
        for(int i = 1; i < n; i++)
            maiores_pre[i] = (a[i-1] >= 0) + maiores_pre[i-1];

        int qtd = 0, ans = 0;
        for(int i = n-1; i >= 0; i--) {
            if(a[i] == mn.first) {
                ans += pot[qtd + maiores_pre[i]]; ans %= mod;
                qtd++;
            } else if(a[i] - 2*mn.first) {
                qtd++;
            }
        }

        printf("%d\n", ans);
    }
}
