#include <bits/stdc++.h>

constexpr int maxn = 3010;

std::vector<int> a[maxn];

int pos[maxn];

int prev[maxn], next[maxn];

int get(int l, int r, int k) {
    int ans = 0;
    for(int rep = 0; rep < k; rep++, l = prev[l], r = prev[r]) {
        int sz = pos[next[l]] - pos[l];
        ans += sz * (pos[r] - pos[next[l]]) + (sz) * (sz-1) / 2;
        if(!l) break;
    }
    return ans;
}

int main() {
    int r, c, n, k; scanf("%d %d %d %d", &r, &c, &n, &k);

    for(int i = 1; i <= n; i++) {
        int x, y; scanf("%d %d", &x, &y);
        a[x].push_back(i);
        pos[i] = y;
    }

    pos[0] = 0;
    for(int i = 1; i <= k+1; i++)
        pos[n+i] = c+1, next[n+i] = n+i+1, prev[n+i] = n+i-1;

    prev[n+1] = -1;
    next[0] = -1;

    long long ans = 0;
    for(int i = 1; i <= r; i++) {

        std::vector<int> aq;
        for(int j = i; j <= r; j++)
            for(int x : a[j])
                aq.push_back(x);
        std::sort(aq.begin(), aq.end(), [](int x, int y){ return pos[x] < pos[y]; });

        if(!aq.size()) { ans += 1ll*(r-i+1)*c*(c+1)/2; continue; }

        prev[n+1] = aq.back();
        next[aq.back()] = n+1;
        prev[aq.front()] = 0;
        next[0] = aq.front();

        for(int j = 1; j < (int)(aq.size()); j++)
            prev[aq[j]] = aq[j-1], next[aq[j-1]] = aq[j];

        int here = get(aq.back(), n+k, n+10);

        for(int j = r; j >= i; j--) {
            ans += here;
            for(int x : a[j]) {
                int L = x, R = L;
                for(int rep = 0; rep < k; rep++, R = next[R]);
                here -= get(L, R, k+1);

                L = prev[x], R = L;
                next[prev[x]] = next[x];
                prev[next[x]] = prev[x];

                for(int rep = 0; rep < k; rep++, R = next[R]);
                here += get(L, R, k);
            }
        }
    }

    printf("%lld\n", 1ll*(r*(r+1)/2)*(c*(c+1)/2) - ans);
}
