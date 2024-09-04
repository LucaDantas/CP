#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())

using ll = long long;

ll solve(const vector<int> &a, int l, int r) {
    if(l > r) return 0;

    int m = (l+r)>>1;
    ll ans = solve(a, l, m-1) + solve(a, m+1, r);

    vector<int> v[2];

    auto reduce = [](int val) { while(val && !(val&1)) val >>= 1; return val; };

    int cnt0[2] = {1, 1};
    auto add = [&](int i, int k) {
        cnt0[k] += !v[k].back() && !reduce(abs(a[i]-a[m]));
        v[k].push_back(__gcd(v[k].back(), reduce(abs(a[i]-a[m]))));
    };

    v[0].push_back(0);
    v[1].push_back(0);
    for(int i = m-1; i >= l; i--)
        add(i, 0);
    for(int i = m+1; i <= r; i++)
        add(i, 1);

    ans += 1ll * cnt0[0] * cnt0[1];

    for(int i = sz(v[0])-1, ptr = 0; i >= 0; i--) {
        while(ptr < sz(v[1]) && __gcd(v[0][i], v[1][ptr]) != 1)
            ptr++;
        ans += sz(v[1]) - ptr;
    }

    return ans;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n);
        for(int &x : a)
            scanf("%d", &x);
        printf("%lld\n", solve(a, 0, n-1));
    }
}
