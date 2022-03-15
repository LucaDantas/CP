#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, maxk = 210;

int a[maxn], suf[maxn];

int itv(int l, int r) { return suf[l] - suf[r+1]; }

long long dp[maxn][2];
int opt[maxn][maxk];

void solve(int l, int r, int l2, int r2, int k) {
	if(l > r) return;

	int m = (l+r) >> 1;
	
	pair<long long, int> ans;
	for(int i = min(m-1, r2); i >= l2; i--)
		ans = max(ans, {dp[i][0] + 1ll * suf[m+1] * itv(i+1, m), i});

	dp[m][1] = ans.first;
	opt[m][k] = ans.second;

	solve(l, m-1, l2, ans.second, k);
	solve(m+1, r, ans.second, r2, k);
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", a+i);
	
	for(int i = n; i >= 1; i--)
		suf[i] = suf[i+1] + a[i];

	for(int i = 1; i < n; i++)
		dp[i][0] = 1ll * suf[i+1] * itv(1, i);

	for(int i = 2; i <= k; i++) {
		solve(1, n-1, 1, n-1, i);
		for(int j = 1; j <= n; j++)
			dp[j][0] = dp[j][1];
	}
	
	pair<long long, int> best;
	for(int i = 1; i < n; i++)
		best = max(best, {dp[i][0], i});
	
	vector<int> ans;
	int i = best.second;
	for(int j = 0; j < k; j++)
		ans.push_back(i), i = opt[i][k-j];
	
	printf("%lld\n", best.first);
	reverse(ans.begin(), ans.end());
	for(int x : ans)
		printf("%d ", x);
	puts("");
}
