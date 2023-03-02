#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

struct BIT {
    int bit[maxn];
    BIT() { for(int i = 0; i < maxn; i++) bit[i] = -maxn; }
    void upd(int x, int v) {
        for(x++; x < maxn; x += x&-x)
            bit[x] = max(bit[x], v);
    }
    int query(int x) {
        int ans = -maxn;
        for(x++; x > 0; x -= x&-x)
            ans = max(ans, bit[x]);
        return ans;
    }
} bit;

int main() {
    int n; scanf("%d", &n);
    vector<long long> a(n);
    for(long long& x : a)
        scanf("%lld", &x);
    for(int i = 1; i < n; i++)
        a[i] += a[i-1];
    vector<long long> mp = a;
    mp.push_back(0);
    sort(mp.begin(), mp.end());
    for(int i = 0; i < n; i++)
        a[i] = lower_bound(mp.begin(), mp.end(), a[i]) - mp.begin();
    bit.upd(lower_bound(mp.begin(), mp.end(), 0) - mp.begin(), 1);
    int ans = -maxn;
    for(int i = 0; i < n; i++) {
        int aq = max(0, bit.query(a[i]) + i); // posso pegar alguém da minha altura também
        aq = ans = max(ans, aq);
        bit.upd(a[i], aq - i);
    }
    printf("%d\n", max(0, ans));
}
