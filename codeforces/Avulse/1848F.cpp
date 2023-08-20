#include <bits/stdc++.h>
using namespace std;

bool check(vector<int>& a) { for(int x : a) if(x) return 0; return 1; }

int main() {
    int n; scanf("%d", &n);
    vector<int> a(n), aux(n);
    for(int& x : a)
        scanf("%d", &x);
    if(check(a)) return puts("0"), 0;
    int ans = 0;
    for(int b = 31-__builtin_clz(n); b >= 0; b--) {
        for(int i = 0; i < n; i++)
            aux[i] = a[i] ^ a[(i-(1<<b)+n)%n];
        if(!check(aux))
            ans += (1 << b), a = aux;
    }
    printf("%d\n", ans+1);
}
