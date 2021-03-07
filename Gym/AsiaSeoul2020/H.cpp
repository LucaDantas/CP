#include<cstdio>
#include<bitset>

// For a triplet to work a + c == 2*b
constexpr int maxn = 12e4+10, shift = 30000;

std::bitset<maxn> a, b;

int main() {
	long long ans = 0;
	int n; scanf("%d", &n);
	for(int i = 0, x; i < n; i++)
		scanf("%d", &x), a.set(x+shift);
	scanf("%d", &n);
	for(int i = 0, x; i < n; i++)
		scanf("%d", &x), b.set((x+shift)<<1);
	scanf("%d", &n);
	for(int i = 0, x; i < n; i++)
		scanf("%d", &x), ans += ((a<<(x+shift))&b).count();
	printf("%lld\n", ans);
}