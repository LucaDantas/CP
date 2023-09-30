#include <bits/stdc++.h>
using namespace std;

inline void opa(multiset<int>& a, multiset<int>& b) {
    if(*a.begin() < *b.rbegin()) {
        a.insert(*b.rbegin());
        b.insert(*a.begin());
        a.erase(a.begin());
        b.erase(b.find(*b.rbegin()));
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);
        multiset<int> a, b;
        int maior = 0, menor = 0x3f3f3f3f;
        for(int i = 0, x; i < n; i++)
            scanf("%d", &x), a.insert(x), maior = max(maior, x), menor = min(menor, x);
        for(int i = 0, x; i < m; i++)
            scanf("%d", &x), b.insert(x), maior = max(maior, x), menor = min(menor, x);
        for(int i = 1; i <= k; i++) {
            if(*a.begin() == menor && *b.rbegin() == maior)
                k = ((k-i)%2) + i;
            if(i&1) {
                opa(a, b);
            } else {
                opa(b, a);
            }
        }
        long long soma = 0;
        for(int x : a)
            soma += x;
        printf("%lld\n", soma);
    }
}
