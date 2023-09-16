#include <bits/stdc++.h>
using namespace std;

int query(int x) {
    printf("? %d\n", x);
    fflush(stdout);
    int ans; scanf("%d", &ans);
    return ans;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        int ans = 0;
        int mod = n%k;
        ans = query(1) ^ query(mod/2+1);
        for(int i = mod+1; i <= n; i += k)
            ans ^= query(i);
        printf("! %d\n", ans);
        fflush(stdout);
    }
}
