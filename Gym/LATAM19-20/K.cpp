#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+10;

char s[maxn];

int main() {
    scanf(" %s", s);
    int n = (int)(strlen(s));
    vector<long long> c(1, 1);
    auto mult = [&](int r) {
         vector<long long> aux(c.size()+1);
         aux[0] = -r * c[0];
         for(int i = 1; i < (int)(c.size()); i++)
             aux[i] = -r * c[i] + c[i-1];
         aux.back() = c.back();
         c = aux;
    };
    for(int i = 1; i < n; i++)
        if(s[i] != s[i-1])
            mult(2*i+1);
    if(s[n-1] == 'A')
        for(long long& x : c)
            x = -x;
    printf("%ld\n", c.size()-1);
    reverse(c.begin(), c.end());
    for(long long x : c)
        printf("%lld ", x);
    puts("");
}
