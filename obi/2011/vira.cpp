#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10, mod = 10007;

int a[maxn], dp[maxn][2], pref[maxn][2], suf[maxn][2];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char c; scanf(" %c", &c);
		a[i] = c=='P';
	}
	dp[1][1] = 1;
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			pref[j][1] = dp[j][1] + pref[j-1][1];
			pref[j][0] = dp[j][0] + pref[j-1][0];

			suf[i-j+1][1] = dp[i-j+1][1] + suf[i-j+2][1];
			suf[i-j+1][0] = dp[i-j+1][0] + suf[i-j+2][0];

			if(pref[j][0] >= mod) pref[j][0] -= mod;
			if(pref[j][1] >= mod) pref[j][1] -= mod;

			if(suf[i-j+1][0] >= mod) suf[i-j+1][0] -= mod;
			if(suf[i-j+1][1] >= mod) suf[i-j+1][1] -= mod;
		}
		for(int j = 1; j <= i; j++)
			dp[j][1] = suf[j][!a[i-1]], dp[j][0] = pref[j-1][a[i-1]];
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans += dp[i][a[n]];
	printf("%d\n", ans%mod);
}