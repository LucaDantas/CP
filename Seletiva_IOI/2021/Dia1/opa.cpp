#include <cstdio>

int main() {
	int n, k; scanf("%d %d", &n, &k);
	if(n > 2*k) printf("%d 0\n", n - 2*k - (1 << (31 - __builtin_clz(n - 2*k))));
	else printf("0 %d\n", k - (n-1)/2);
}
