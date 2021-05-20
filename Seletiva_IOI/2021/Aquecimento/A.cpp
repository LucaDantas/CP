#include <cstdio>
#include <algorithm>

constexpr int maxn = 3e5+10;

int a[maxn], dif[maxn];

int main() {
	int n, s; scanf("%d %d", &n, &s);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	std::sort(a, a+n);
	for(int i = 0; i < n-1; i++)
		dif[i] = a[i+1] - a[i];
	std::sort(dif, dif+n-1);
	std::reverse(dif, dif+n-1);
	long long ans = 1ll * s + a[n-1] - a[0];
	for(int i = 0; i < n-1; i++)
		if(dif[i] > s) ans += s - dif[i];
	printf("%lld\n", ans);
}