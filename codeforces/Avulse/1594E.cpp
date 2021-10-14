#include <cstdio>

constexpr int mod = 1e9+7;

int power(int b, long long e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int main() {
	int k; scanf("%d", &k);
	printf("%lld\n", 6ll * power(4, (1ll << k) - 2) % mod);
}
