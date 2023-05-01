#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

ull p[12];

bool valid(ull x, ull y, ull z, char op) {
    if(x > z || y > z) return 0;
    if(op == '+')
        return x + y == z;
    return x * y == z;
}

int main() {
    p[0] = 1;
    for(int i = 1; i < 12; i++)
        p[i] = p[i-1] * 10ll;

    ull x, y, z; char op; scanf("%llu %c %llu = %llu", &x, &op, &y, &z);

    for(int i = 1; i < 12; i++) {
        for(int j = 1; j < 12; j++) {
            vector<ull> v = {x, y, z};
            for(int a : {0, 1, 2}) for(int b = a+1; b < 3; b++) if(v[a] >= p[i] && v[b] >= p[j]) {
                auto aux = v;
                aux[a] = v[a] % p[i] + (v[b] / p[j]) * p[i];
                aux[b] = v[b] % p[j] + (v[a] / p[i]) * p[j];
                if(valid(aux[0], aux[1], aux[2], op))
                    printf("%llu %c %llu = %llu\n", aux[0], op, aux[1], aux[2]);
            }
        }
    }
}
