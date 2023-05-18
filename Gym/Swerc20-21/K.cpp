#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())

using ll = long long;

struct hash_interval
{
	ll c, mod;
	vector<ll> h, p;
	hash_interval(const string &s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1)
	{
		p[0] = 1;
		h[0] = 0;
		for (int i = 0; i < sz(s); i++)
		{
			h[i + 1] = (c * h[i] + s[i]) % mod;
			p[i + 1] = (c * p[i]) % mod;
		}
	}

	// Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
	ll get(int a, int b)
	{
		return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    string s; cin >> s;

    hash_interval hs1(s, 137, 1000002803), hs2(s, 137, 1000001699);

    auto check = [&](int sz) {
        vector<array<ll,3>> a;

        for(int i = 0; i + sz <= sz(s); i++)
            a.push_back({hs1.get(i, i+sz-1), hs2.get(i, i+sz-1), i});

        sort(a.begin(), a.end());

        long long best = 0x3f3f3f3f;

        for(int i = 0; i < sz(a); i++) {
            if((!i || (a[i][0] != a[i-1][0] || a[i][1] != a[i-1][1])) && (i == sz(a)-1 || (a[i][0] != a[i+1][0] || a[i][1] != a[i+1][1])))
                best = min(best, a[i][2]);
        }
        return best == 0x3f3f3f3f ? -1ll : best;
    };

    int ans = 0, l = 1, r = sz(s);
    while(l <= r) {
        int m = (l+r)>>1;
        if(check(m) != -1)
            ans = m, r = m-1;
        else
            l = m+1;
    }
    cout << s.substr(check(ans), ans) << '\n';
}