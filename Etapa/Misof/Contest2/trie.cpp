#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 16;

int dp[1<<maxn], cost[1<<maxn];

int cnt[maxn][30], opa[30];

int comum(int mask) {
	memset(opa, 0x3f, sizeof opa);
	for(int i = 0; i < maxn; i++) {
		if(mask & (1 << i))
			for(int j = 0; j < 26; j++)
				opa[j] = min(opa[j], cnt[i][j]);
	}
	int ans = 0;
	for(int i = 0; i < 26; i++)
		ans += opa[i];
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr);
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		string s; cin >> s;
		for(char c : s)
			++cnt[i][c-'a'];
	}
	memset(dp, 0x3f, sizeof dp);
	for(int i = 0; i < n; i++)
		dp[1<<i] = comum(1<<i);
	for(int mask = 1; mask < (1 << n); mask++) {
		cost[mask] = comum(mask);
		for(int sub = (mask-1)&mask; sub>0; sub = (sub-1)&mask)
			dp[mask] = min(dp[mask], (-cost[mask] + dp[sub]) + cost[mask] - cost[mask] + dp[mask^sub]);
	}
	cout << dp[(1<<n)-1]+1 << '\n';
}