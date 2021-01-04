#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 5e5+10, mod = 1e9+7;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vector<ll> a(n), b(64);
		for(ll& x : a) {
			scanf("%lld", &x);
			for(int i = 0; i < 60; i++)
				if(x&(1ll<<i))
					++b[i];
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int here = 0, here2 = 0;
			for(int j = 0; j < 60; j++) {
				if(a[i]&(1ll<<j)) {
					here = (here + 1ll*n*((1ll<<j)%mod)%mod) % mod;
					here2 = (here2 + 1ll*(b[j])*((1ll<<j)%mod)%mod) % mod;
				}
				else
					here = (here + 1ll*b[j]*((1ll<<j)%mod)%mod) % mod;
			}
			ans += 1ll*here*here2%mod;
			if(ans >= mod) ans -= mod;
		}
		printf("%d\n", ans);
	}
}