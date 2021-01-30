#include<bits/stdc++.h>
using namespace std;

constexpr int maxb = 30, mod = 1000000007;

int dp[2][2][2][2];
int dp2[2][2][2][2];

bool on(int x, int i) { return (x&(1<<i)) > 0; }

void add(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

void sub(int& a, int b) {
	a -= b;
	if(a < 0) a += mod;
}

int solve(int x, int y, int k) {
	if(min(x, y) < 0) return 0;
	memset(dp, 0, sizeof dp);
	memset(dp2, 0, sizeof dp2);
	dp[0][0][0][0] = 1;
	for(int i = maxb; i >= 0; i--) {
		for(int mask = 0; mask < (1 << 3); mask++) {
			int f1 = mask&1, f2 = (mask&2)>>1, f3 = (mask&4)>>2;
			int me = dp[0][f1][f2][f3];
			int me2 = dp2[0][f1][f2][f3];
			if(!me) continue;
			// 1 - 1
			if((f1 || on(x, i)) && (f2 || on(y, i)))
				add(dp[1][f1][f2][f3||on(k, i)], me),
				add(dp2[1][f1][f2][f3||on(k, i)], me2);
			// 1 - 0
			if((f1 || on(x, i)) && (on(k, i) || f3))
				add(dp[1][f1][f2||on(y, i)][f3], me),
				add(dp2[1][f1][f2||on(y, i)][f3], (int)((1ll*me*(1<<i)+me2)%mod));
			// 0 - 1
			if((f2 || on(y, i)) && (on(k, i) || f3))
				add(dp[1][f1||on(x, i)][f2][f3], me),
				add(dp2[1][f1||on(x, i)][f2][f3], (int)((1ll*me*(1<<i)+me2)%mod));
			// 0 - 0
			add(dp[1][f1||on(x, i)][f2||on(y, i)][f3||on(k, i)], me);
			add(dp2[1][f1||on(x, i)][f2||on(y, i)][f3||on(k, i)], me2);
		}

		for(int mask = 0; mask < (1 << 3); mask++) {
			int f1 = mask&1, f2 = (mask&2)>>1, f3 = (mask&4)>>2;
			dp[0][f1][f2][f3] = dp[1][f1][f2][f3];
			dp[1][f1][f2][f3] = 0;

			dp2[0][f1][f2][f3] = dp2[1][f1][f2][f3];
			dp2[1][f1][f2][f3] = 0;
		}
	}
	int ans = 0;
	for(int mask = 0; mask < (1 << 3); mask++)
		add(ans, (dp[0][on(mask, 0)][on(mask, 1)][on(mask, 2)]+dp2[0][on(mask, 0)][on(mask, 1)][on(mask, 2)])%mod);
	return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int x1, y1, x2, y2, k;
		scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &k);
		--x1, --x2, --y1, --y2, --k;
		int ans = solve(x2, y2, k);
		sub(ans, solve(x1-1, y2, k));
		sub(ans, solve(x2, y1-1, k));
		add(ans, solve(x1-1, y1-1, k));
		printf("%d\n", ans);
	}
}