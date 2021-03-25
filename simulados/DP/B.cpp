#include <cstdio>
#include <cstring>

constexpr int maxn = 32, mod = 1000000007;

int dp[maxn][2][2]; // [flag x][flag y]

void add(int& a, long long b) { a += (int)b; if(a >= mod) a -= mod; }

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		memset(dp, 0, sizeof dp);
		int x, y; scanf("%d %d", &x, &y);
		int mbx = 31 - __builtin_clz(x), mby = 31 - __builtin_clz(y);
		auto on = [](int a, int b) { return (a&(1<<b)) > 0; };
		int ans = 0;
		dp[0][1][1] = 1;
		for(int i = 1; i < maxn; i++) {
			for(int mask = 0; mask < (1 << 2); mask++) {
				int f1 = on(mask, 0), f2 = on(mask, 1);
				// Represent the values I'm taking from the last dp

				// turn on x
				add(dp[i][f1 && on(x, i-1)][f2 || on(y, i-1)], dp[i-1][f1][f2]);
				if( ( mbx >= i || ( f1 && on(x, i-1) ) ) && ( mby >= i || ( f2 || on(y, i-1) ) ) )
					add(ans, 1ll * i * dp[i-1][f1][f2] % mod);

				// turn on y
				add(dp[i][f1 || on(x, i-1)][f2 && on(y, i-1)], dp[i-1][f1][f2]);
				if( ( mbx >= i || ( f1 || on(x, i-1) ) ) && ( mby >= i || ( f2 && on(y, i-1) ) ) )
					add(ans, 1ll * i * dp[i-1][f1][f2] % mod);

				// don't turn anything on
				add(dp[i][f1 || on(x, i-1)][f2 || on(y, i-1)], dp[i-1][f1][f2]);
			}
		}
		printf("%d\n", ans);
	}
}