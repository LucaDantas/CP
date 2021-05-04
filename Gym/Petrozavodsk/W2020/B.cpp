#include<cstdio>
#include <cstring>
using namespace std;

long long f[1<<20], F[1<<20];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		memset(f, 0, sizeof f);
		memset(F, 0, sizeof F);
		for(int i = 0, x; i < n; i++)
			scanf("%d", &x), ++f[x], ++F[x];
		for(int i = 0; i < 20; i++)
			for(int mask = 0; mask < (1 << 20); mask++)
				if(mask & (1<<i))
					F[mask] += F[mask^(1<<i)];
		long long ans = 0;
		for(int i = 0; i < 1<<20; i++)
			ans += 1ll*F[i]*f[i];
		printf("%lld\n", ans);
	}
}