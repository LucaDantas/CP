#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, logn = 31;

int a[maxn], df[logn];

int valid(int x) {
    bool vi = x&1;
    for(int i = 1; i < logn; i++) {
        if(!(x&(1<<(i-1))) && (x&(1<<i))) {
            if(vi) {
                return 0;
            } else {
                vi = 1;
            }
        }
    }
    return 1;
}

int up(int x) {
    return 32-__builtin_clz(x);
}

int down(int x) {
    int k = 0;
    while(!(x&1))
        ++k, x >>= 1;
    return k;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        long long sum = 0;
        for(int i = 0; i < n; i++)
            scanf("%d", a+i), sum += a[i];
        if(sum%n) { puts("No"); continue; }
        int avg = (int) (sum/n);
        memset(df, 0, sizeof df);
        bool ok = 1;
        for(int i = 0; i < n; i++) if(a[i] != avg) {
            int d = a[i] - avg, sign = d > 0 ? 1 : -1;
            if(valid(abs(d)))
                df[up(abs(d))] += sign, df[down(abs(d))] -= sign;
            else ok = 0;
        }
        for(int i = 0; i < logn; i++)
            ok &= df[i] == 0;
        puts(ok ? "Yes" : "No");
    }
}
