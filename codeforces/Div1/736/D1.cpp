#include <cstdio>

constexpr int maxn = 6000 + 10;

int pt[maxn], cnt[4];

int main() {
	int n; scanf("%d", &n);
	long long ans = 0;
	for(int i = 0, a, b; i < n; i++) {
		scanf("%d %d", &a, &b), pt[i] = (a>>1&1)<<1 | (b>>1&1);
		for(int j = 0; j < 4; j++)
			cnt[j] = 0;
		for(int j = 0; j < i; j++)
			++cnt[pt[i]^pt[j]];
		ans += 1ll * cnt[0] * (i - cnt[0]) + 1ll * cnt[0] * (cnt[0]-1) / 2;
		for(int j = 1; j < 4; j++)
			ans += 1ll * cnt[j] * (cnt[j] - 1) / 2;
	}
	printf("%lld\n", ans);
}
