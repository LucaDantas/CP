#include <bits/stdc++.h>
using namespace std;

constexpr int logn = 30;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<pair<int,int>> itv(n);
        for(auto& [l, r] : itv)
            scanf("%d %d", &l, &r);
        function<bool(int)> check = [&](int val) {
            for(auto [l, r] : itv) {
                int so_em_val = (val ^ l) & val, maior = 1 << (31-__builtin_clz(so_em_val)), mask = maior-1;
                int menor_que_tem_val = ((l | mask) ^ mask) | val;
                if(menor_que_tem_val > r)
                    return 0;
            }
            return 1;
        };
        int val = 0;
        for(int l = logn; l >= 0; l--)
            if(check(val | (1 << l)))
                val |= (1<<l);
        printf("%d\n", val);
    }
}
