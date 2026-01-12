#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {1, -1, 1, -1};
const int dy[4] = {1, -1, -1, 1};
constexpr int inf = 0x3f3f3f3f;

using ll = long long;

int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<pair<int,int>> pos;
    int l = inf, r = -inf, u = -inf, d = inf;
    for(int i = 0, x, y; i < n; i++) {
        scanf("%d %d", &x, &y), pos.push_back({x, y});
        l = min(l, x);
        r = max(r, x);
        u = max(u, y);
        d = min(d, y);
    }

    if(n == 1) {
        puts("1");
        return 0;
    }

    ll ans = 0;

    for(int i = 0; i < n; i++) {
        auto [x, y] = pos[i];
        for(int rep = 0; rep < 4; rep++) {
            int new_l = min(l, x + dx[rep] * k);
            int new_r = max(r, x + dx[rep] * k);

            int new_u = max(u, y + dy[rep] * k);
            int new_d = min(d, y + dy[rep] * k);

            ans = max(ans, 1ll * (1 + new_r - new_l) * (1 + new_u - new_d));
        }
    }

    int s1 = r - l + 1;
    int s2 = u - d + 1;

    if(abs(s1 - s2) <= k)
        ans = max(ans, 1ll * ((s1 + s2 + k) / 2) * ((s1 + s2 + k + 1) / 2));

    ans = max({ans, 1ll * (s1 + k) * s2, 1ll * s1 * (s2 + k)});
    
    printf("%lld\n", ans);
}
