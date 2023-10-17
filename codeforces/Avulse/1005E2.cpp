#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
#define sz(a) (int)(a.size())
#define all(a) (a).begin(), (a).end()

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

int main() {
    int n, m; scanf("%d %d", &n, &m);
    FT2 bit(4e5+10);
    vector<int> a(n+1), s(n+1), e(n+1);
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        s[i] = s[i-1], e[i] = e[i-1];
        int& x = a[i];
        scanf("%d", &x);
        if(x == m) ++e[i];
        else s[i] += x < m ? -1 : 1;
        mp[-s[i]+e[i]] = 0;
        mp[-s[i]+e[i]-1] = 0;
    }
    mp[-1] = 0;
    int cnt = 0;
    for(auto& it : mp)
        it.second = ++cnt;
    for(int i = 1; i <= n; i++) {
        int x = s[i] - e[i], y = -s[i] - e[i];
        bit.fakeUpdate(mp[-x-1], -y);
    }
    bit.fakeUpdate(mp[-1], 0);
    bit.init();
    bit.update(mp[-1], 0, 1);
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = s[i] - e[i], y = -s[i] - e[i];
        ans += bit.query(mp[-x], -y);
        bit.update(mp[-x-1], -y, 1);
    }
    printf("%lld\n", ans);
}
