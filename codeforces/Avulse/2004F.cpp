#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n);
        for(int &x : a)
            scanf("%d", &x);
        map<int, int> mp;
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            int soma = 0;
            for(int j = i; j < n; j++) {
                soma += a[j];
                ans += (j-i)-mp[soma];
                mp[soma]++;
            }
        }

        printf("%lld\n", ans);
    }
}
