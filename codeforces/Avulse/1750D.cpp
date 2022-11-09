#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, mod = 998244353;

int f[maxn];
vector<int> pr;

int gcd(int a, int b) { return !b?a:gcd(b,a%b); }

void sieve() {
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) f[i] = i, pr.push_back(i);
        for(int j = 0; j < (int)(pr.size()) && pr[j] <= f[i] && i*pr[j] < maxn; j++)
            f[i*pr[j]] = pr[j];
    }
}

vector<int> get(int x, vector<int> aq) {
    vector<int> ans;

    for(int p : aq)
        if(x%p == 0) {
            ans.push_back(p);
            while(x%p == 0) x /= p;
        }

    if(x > 1)
        ans.push_back(x);

    return ans;
}

int main() {
    sieve();
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        vector<int> a(n);
        for(int& x : a)
            scanf("%d", &x);

        bool ok = 1;
        for(int i = 1; i < n; i++)
            ok &= gcd(a[i], a[i-1]) == a[i];
        if(!ok) { puts("0"); continue; }

        vector<int> aq = get(a[0], pr);

        int ans = 1;

        for(int i = 1; i < n; i++) {
            vector<int> bad = get(a[i-1]/a[i], aq);
            int maximum = m/a[i], ruins = 0;
            for(int mask = 1; mask < (1 << (bad.size())); mask++) {
                int sign = (__builtin_popcount(mask) & 1) ? 1 : -1; // se for impar adiciono, senao removo
                int val = 1;
                for(int b = 0; b < (int)bad.size(); b++)
                    if(mask & (1<<b)) val *= bad[b];
                ruins += (maximum / val) * sign;
            }
            ans = (int)(1ll * ans * (maximum - ruins) % mod);
        }
        
        printf("%d\n", ans);
    }
}
