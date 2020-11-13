#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define pb push_back
#define sz(a) (int)(a.size())

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

ll power(ll x, int b) {
	ll ans = 1;
	while(b) {
		if(b&1) {
			if((__int128)ans*x > inf)
				return inf;
			 ans *= x;
		}
		if((__int128)x*x > inf)
			x = inf;
		else x *= x;
		b >>= 1;
	}
	return ans;
}

int raiz(ll x, int b) {
	int l = 1, r = 1e9, ans = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(power(m, b) <= x)
			ans = m, l = m+1;
		else r = m-1;
	}
	return ans;
}

ll ans = 0, n;

vector<pii> ei;

void opa(int now, int val, int par) {
	if(now == sz(pr)) {
		if(val == 1)
			return;
		ei.pb({val, par});
	} else {
		if(pr[now]*val <= 60ll)
			opa(now+1, pr[now]*val, par^1);
		opa(now+1, val, par);
	}
}

int main() {
	opa(0, 1, 0);
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		ans = 0;
		for(pii x : ei)
			ans += (x.second?1:-1)*(raiz(n, x.first)-1);
		printf("%lld\n", n - 1 - ans);
	}
}