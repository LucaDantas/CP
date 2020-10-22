#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define pb push_back

constexpr int maxn = 1e5+10;

vector<ll> base;

ll check(ll x) {
	for(ll y : base)
		x = min(x, x^y);
	return x;
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		ll v; scanf("%lld", &v);
		ll x = check(v);
		if(x) base.pb(x);
	}
	ll ans = 0;
	for(ll x : base)
		ans = max(ans, ans^x);
	printf("%lld\n", ans);
}