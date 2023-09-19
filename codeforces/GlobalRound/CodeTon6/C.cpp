#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 0x3f3f3f3f;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        vector<int> a(n), mn(k+1, inf), mx(k+1, -inf);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            mn[a[i]] = min(mn[a[i]], i);
            mx[a[i]] = max(mx[a[i]], i);
        }
        int l = inf, r = -inf;
        vector<int> ans;
        for(int i = k; i >= 1; i--) {
            if(mn[i] == inf) ans.push_back(0);
            else {
                l = min(l, mn[i]);
                r = max(r, mx[i]);
                ans.push_back((r-l+1)<<1);
            }
        }
        reverse(ans.begin(), ans.end());
        for(int x : ans)
            printf("%d ", x);
        puts("");
    }
}
