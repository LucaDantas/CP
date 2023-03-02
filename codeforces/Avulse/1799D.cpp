#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        long long ans = 0;
        vector<int> a(n);
        for(int& x : a)
            scanf("%d", &x), --x;
        vector<int> cold(k), hot(k);
        for(int& x : cold)
            scanf("%d", &x);
        for(int& x : hot)
            scanf("%d", &x);
        vector<int> aux; aux.push_back(a[0]);
        for(int i = 1; i < n; i++)
            if(a[i] == a[i-1])
                ans += hot[a[i]];
            else
                aux.push_back(a[i]);
        a = aux;
        n = a.size();
        vector<int> last(k, -1);
        vector<long long> dp(n);
        for(int i = 0; i < n; i++) {
            ans += cold[a[i]];
            if(i) dp[i] = dp[i-1];
            if(last[a[i]] != -1)
                dp[i] = max(dp[i], dp[last[a[i]] + 1] + (cold[a[i]] - hot[a[i]]));
            last[a[i]] = i;
        }
        printf("%lld\n", ans - dp[n-1]);
    }
}
