#include <cstdio>

int dp[1<<8][1<<8];

int main() {
	int n; scanf("%d", &n);
	while(n--) {
		int t, x; scanf("%d %d", &t, &x);
		int esq = x >> 8, dir = x & ((1 << 8) - 1);
		if(t == 1 || t == 2) {
			int v = t == 1 ? 1 : -1;
			for(int mask = 0; mask < (1 << 8); mask++)
				if((mask & esq) == mask)
					dp[mask][dir] += v;
		} else {
			int ans = 0;
			for(int mask = dir; mask < (1 << 8); mask++)
				if((mask & dir) == dir)
					ans += dp[esq][mask];
			printf("%d\n", ans);
		}
	}
}
