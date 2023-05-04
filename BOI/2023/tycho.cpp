#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

long long a[maxn], dp[maxn];

map<long long,int> mp;

struct BIT1 {
    long long bit[maxn];
    BIT1() { memset(bit, 0x3f, sizeof bit); }
    void upd(int x, long long v) {
        for(x++; x < maxn; x += x&-x)
            bit[x] = min(bit[x], v);
    }
    long long query(int x) {
        long long ans = inf;
        for(x++; x > 0; x -= x&-x)
            ans = min(ans, bit[x]);
        return ans;
    }
} pref;

struct BIT2 {
    long long bit[maxn];
    BIT2() { memset(bit, 0x3f, sizeof bit); }
    void upd(int x, long long v) {
        for(x++; x > 0; x -= x&-x)
            bit[x] = min(bit[x], v);
    }
    long long query(int x) {
        long long ans = inf;
        for(x++; x < maxn; x += x&-x)
            ans = min(ans, bit[x]);
        return ans;
    }
} suf;

int main() {
    long long b, p, d, n; scanf("%lld %lld %lld %lld", &b, &p, &d, &n);

    for(int i = 1; i <= n; i++)
        scanf("%lld", a+i), mp[a[i]%p] = 0;
    mp[0] = 0;

    int cnt = 0;
    for(auto& it : mp)
        it.second = ++cnt;

    pref.upd(mp[0], 0);
    suf.upd(mp[0], 0);
    for(int i = 1; i <= n; i++) {
        long long grp = a[i] / p;
        int pos = mp[a[i]%p];

        dp[i] = min(pref.query(pos-1) + p, suf.query(pos) - d) + grp * (d+p);

        pref.upd(pos, dp[i] - grp * (d + p));
        suf.upd(pos, dp[i] - grp * (d + p));
    }

    long long ans = inf;
    for(int i = 0; i <= n; i++)
        ans = min(ans, dp[i] + b - a[i] + ((b - a[i] - 1) / p) * d);
    printf("%lld\n", ans);
}
