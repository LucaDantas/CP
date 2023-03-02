#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        int g = 0, mx = 0;
        for(int i = 0; i < n; i++) {
            int x; scanf("%d", &x);
            g = __gcd(g, x);
            mx = max(mx, x);
        }
        printf("%d\n", mx / g);
    }
}
