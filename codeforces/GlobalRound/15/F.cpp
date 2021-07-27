#include <cstdio>
#include <algorithm>

constexpr int maxn = 2e5+10, mod = 998244353;

int x[maxn], pref[maxn], dp, ans;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1, y, s; i <= n; i++) {
		scanf("%d %d %d", &x[i], &y, &s);
		int back = std::lower_bound(x+1, x+i+1, y) - x;
		dp = (pref[i-1] - pref[back-1] + x[i] - y) % mod;
		if(dp < 0) dp += mod;
		pref[i] = (pref[i-1] + dp) % mod;
		ans += s * dp;
		ans %= mod;
	}
	ans += x[n] + 1;
	ans %= mod;
	printf("%d\n", ans);
}
