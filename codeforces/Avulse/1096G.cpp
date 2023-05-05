#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

ll modpow(ll b, ll e) {
    ll ans = 1;
    while(e) {
        if(e&1) ans = ans * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return ans;
}

typedef vector<ll> vl;
void ntt(vl& a, vl& rt, vl& rev, int n) {
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
                ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
                ai += (ai + z >= mod ? z - mod : z);
    }
}

vl conv(const vl& a, const vl& b) {
    if (a.empty() || b.empty())
        return {};
    int s = sz(a)+sz(b)-1, B = 32 - __builtin_clz(s), n = 1 << B;
    vl L(a), R(b), out(n), rt(n, 1), rev(n);
    L.resize(n), R.resize(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
    ll curL = mod / 2, inv = modpow(n, mod - 2);
    for (int k = 2; k < n; k *= 2) {
        ll z[] = {1, modpow(root, curL /= 2)};
        rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    ntt(L, rt, rev, n); ntt(R, rt, rev, n);
    rep(i,0,n) out[-i & (n-1)] = L[i] * R[i] % mod * inv % mod;
    ntt(out, rt, rev, n);
    return {out.begin(), out.begin() + s};
}

vl& pow(vl b, ll e) {
    static vl ans = {1};
    while(e) {
        if(e&1) ans = conv(ans, b);
        b = conv(b, b);
        e >>= 1;
    }
    return ans;
}

int main() {
    int n, k; scanf("%d %d", &n, &k);
    vl p(10);
    for(int i = 0, x; i < k; i++)
        scanf("%d", &x), p[x] = 1;
    vl pans = pow(p, n>>1);
    ll ans = 0;
    for(ll& x : pans)
        ans += x*x%mod, ans %= mod;
    printf("%lld\n", ans);
}
