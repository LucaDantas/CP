#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        int ans = n;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++)
            scanf("%d %d", &a[i], &b[i]);
        for(int i = 0; i < n-1; i++) {
            long long m = 1ll * b[i] * b[i+1] / __gcd(b[i], b[i+1]);
            if(a[i] % (m/b[i]) == 0 && a[i+1] % (m/b[i+1]) == 0) {
                --ans;
                a[i+1] = __gcd(a[i+1] / (m / b[i+1]), a[i] / (m / b[i]));
                b[i+1] = m;
            }
        }
        printf("%d\n", ans);
    }
}
