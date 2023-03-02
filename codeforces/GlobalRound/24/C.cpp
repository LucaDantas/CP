#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        static map<int, int> cnt; cnt.clear();
        for(int i = 0, x; i < n; i++)
            scanf("%d", &x), cnt[x]++;
        int agr = 0;
        long long ans = n/2;
        for(auto [val, qtd] : cnt) {
            for(int i = 0; i < qtd; i++, agr++)
                ans = max(ans, 1ll * agr * (n-agr) - 1ll*i*(qtd-i));
            ans = max(ans, 1ll * agr * (n-agr));
        }
        printf("%lld\n", ans);
    }
}
