#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int S = 840, maxn = 20000;

bitset<maxn> dp;

int main() {
	ll n; scanf("%lld", &n);
	vector<ll> cnt(8);
	for(ll& x : cnt)
		scanf("%lld", &x);
	ll packs = 0;
	dp.set(0);
	for(int i = 0; i < 8; i++) {
		int sz = S / (i+1);
		if(cnt[i] >= sz) {
			cnt[i] -= sz;
			packs += cnt[i] / sz;
			cnt[i] = sz + (cnt[i]%sz);
		}
		for(int l = 0; cnt[i] > 0; l++) {
			int val = (i+1)*min(1 << l, (int)cnt[i]);
			cnt[i] -= val/(i+1);
			dp |= dp << val;
		}
	}
	ll start = 0, ans = 0;
	if(n >= maxn)
		start = min(n - maxn - ((n-maxn)%S), packs*S);
	packs -= start / S;
	while(start <= n) {
		for(int i = 0; i < maxn && i + start <= n; i++)
			if(dp[i])
				ans = max(ans, i + start);
		start += S;
		if(!packs)
			break;
		packs--;
	}
	printf("%lld\n", ans);
}