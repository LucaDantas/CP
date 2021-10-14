#include <bits/stdc++.h>
using namespace std;

long long choose2(int tam) { return 1ll * tam * (tam-1) / 2; }

int main() {
	long long n; scanf("%lld", &n);
	int l = 0, r = 0x7fffffff, ans = -1;
	while(l <= r) {
		int m = l + (r-l)/2;
		if(choose2(m+1) <= n)
			ans = m, l = m+1;
		else r = m-1;
	}
	printf("%d\n", ans);
}
