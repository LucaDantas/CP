#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, inf = 0x3f3f3f3f;

set<pair<int,int>> st[maxn]; // the sets for each level
// saves the pair (x_position, time)

int t[maxn], a[maxn], v;

bool check(pair<int,int> a, pair<int,int> b) {
    return 1ll*(b.second-a.second)*v >= abs(a.first - b.first);
}

int main() {
    int n; scanf("%d %d", &n, &v);
    st[0].insert({0, 0});
    for(int i = 1; i <= n; i++) 
        scanf("%d", t+i);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int l = 0, r = ans, here = -1;
        while(l <= r) {
            int m = (l+r) >> 1;
            auto it = st[m].lower_bound({a[i], -inf});
            if((it != st[m].end() && check(*it, {a[i], t[i]})) || (it != st[m].begin() && check(*prev(it), {a[i], t[i]})))
                here = m, l = m+1;
            else
                r = m-1;
        }
        if(here == -1) continue;
        st[here+1].insert({a[i], t[i]});
        ans = max(ans, here+1);
    }
    printf("%d\n", ans);
}
