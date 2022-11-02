#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

set<int> bad;
int f[maxn];
vector<int> pr;

void sieve() {
    f[1] = 1;
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) f[i] = i, pr.push_back(i);
        for(int j = 0; j < pr.size() && pr[j] <= f[i] && i * pr[j] < maxn; j++)
            f[i * pr[j]] = pr[j];
    }
}

int value(int x) {
    int ans = 0;
    for(int p : pr)
        while(x % p == 0)
            ans += 1 - 2*bad.count(p), x /= p;
    return ans + (x > 1 ? 1 - 2*bad.count(x) : 0);
}

int main() {
    sieve();
    int n, m; scanf("%d %d", &n, &m);
    vector<int> a(n), pref(n);
    for(int& x : a)
        scanf("%d", &x);
    for(int i = 0; i < m; i++) {
        int x; scanf("%d", &x);
        bad.insert(x);
    }
    pref[0] = a[0];
    for(int i = 1; i < n; i++)
        pref[i] = gcd(a[i], pref[i-1]);
    int ans = 0;
    for(int i = n-1, now = 1; i >= 0; i--) {
        pref[i] /= now;
        if(value(pref[i]) < 0)
            now *= pref[i];
        ans += value(a[i] / now);
    }
    printf("%d\n", ans);
}
