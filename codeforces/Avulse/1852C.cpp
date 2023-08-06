#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        priority_queue<int, vector<int>, greater<int>> q;
        long long ans = 0;
        vector<int> a(n+1);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]), a[i] %= k;
            q.push((a[i] - a[i-1] + k) % k);
            if(a[i] >= a[i-1])
                ans += q.top(), q.pop();
        }
        printf("%lld\n", ans);
    }
}
