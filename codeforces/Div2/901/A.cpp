#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        long long b;
        int a, n; scanf("%d %lld %d", &a, &b, &n);
        vector<int> x(n);
        for(int &y : x)
            scanf("%d", &y), b += min(y, a-1);
        printf("%lld\n", b);
    }
}
