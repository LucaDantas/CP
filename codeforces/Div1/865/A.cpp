#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        long long s = 0, sign = -1; // we want odd - even to be >= 0 so it starts negative
        for(int i = 0, x; i < n; i++)
            scanf("%d", &x), s += sign * x, sign *= -1;
        if(n&1) puts("YES");
        else puts(s >= 0 ? "YES" : "NO");
    }
}
