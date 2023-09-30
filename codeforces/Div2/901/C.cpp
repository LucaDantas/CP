#include <bits/stdc++.h>
using namespace std;

struct Frac {
    __int128 p, q;
    Frac(__int128 _p, __int128 _q) : p(_p), q(_q) { __int128 g = __gcd(p, q); p /= g, q /= g; }
    Frac operator-(const Frac& o) const { return Frac(p*o.q - o.p*q, q*o.q); }
    bool operator<=(const Frac& o) const { return p*o.q <= o.p*q; }
};

int cnt;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        if(__builtin_popcount(m / __gcd(n, m)) != 1)
            puts("-1");
        else {
            long long custo = 0, qtd = n;
            Frac f(n, m), agr(1, 1);
            if(Frac(1, 1) <= f) {
                int sla = n/m;
                f = f-Frac(sla, 1);
                qtd -= m * sla;
            }
            while(qtd > 0) {
                if(agr <= f)
                    f = f - agr, qtd -= m;
                custo += qtd;
                qtd <<= 1;
                agr.q <<= 1;
            }
            printf("%lld\n", custo);
        }
    }
}
