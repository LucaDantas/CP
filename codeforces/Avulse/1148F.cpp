#include <bits/stdc++.h>
using namespace std;

constexpr int logn = 64;

vector<pair<int,long long>> grp[logn];

int main() {
    int n; scanf("%d", &n);
    long long tot = 0;
    for(int i = 0; i < n; i++) {
        int val; long long mask; scanf("%d %lld", &val, &mask);
        grp[63-__builtin_clzll(mask)].push_back({val, mask});
        tot += val;
    }
    int sign = tot < 0 ? 1 : -1;
    long long ans = 0;
    for(int l = 0; l < logn; l++) if(grp[l].size()) {
        long long soma = 0;
        for(auto [val, mask] : grp[l]) {
            if(__builtin_popcountll(mask & ans) & 1)
                val *= -1;
            soma += val;
        }
        if(soma * sign < 0)
            ans |= (1ll << l);
    }
    printf("%lld\n", ans);
}
