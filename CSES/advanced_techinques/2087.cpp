// Solution using Alien's trick
#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e3+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f;

long long lambda, pref[maxn], qtd_pref[maxn];
int a[maxn], n;

pair<long long,int> ans, dp[maxn];

long long qtd_itv(int l, int r) { return qtd_pref[r] - qtd_pref[l-1]; }
long long itv(int l, int r) { return pref[r] - pref[l-1]; }

long long cost(int l, int r) {
	int m = (l+r) >> 1;
	return itv(l, m) - qtd_itv(l, m) * l + qtd_itv(m+1, r) * r - itv(m+1, r);
}

void get() {
	ans = {inf, maxn};
	for(int i = 1; i <= n; i++) {
		// just me
		dp[i] = {qtd_pref[i] * i - pref[i] + lambda, 1};
		for(int last = 1; last < i; last++)
			dp[i] = min(dp[i], {dp[last].first + lambda + cost(last, i), dp[last].second+1});
		ans = min(ans, {dp[i].first + itv(i, n) - qtd_itv(i, n) * i, dp[i].second});
	}
}

int main() {
	int k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pref[i] = pref[i-1] + 1ll * i * a[i];
		qtd_pref[i] = qtd_pref[i-1] + a[i];
	}
	long long l = 0, r = inf, best = inf;
	while(l <= r) {
		lambda = (l+r) >> 1;
		get();
		if(ans.second <= k) best = ans.first - (lambda * k), r = lambda-1;
		else l = lambda+1;
	}
	printf("%lld\n", best);
}