#include <cstdio>

constexpr int maxn = 1e6+10;

int a[maxn];

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 0; i < k; i++)
		scanf("%d", &a[i]);
	a[k] = n+1;
	long long ans = 0;
	for(int i = 2; i < k; i++)
		ans += 1ll * a[i-2] * (a[i+1] - a[i]);
	printf("%lld\n", ans);
}