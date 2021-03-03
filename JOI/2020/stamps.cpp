#include<bits/stdc++.h>

constexpr int maxn = 200+10;

std::pair<int,int> a[maxn];

int dp[maxn][maxn][maxn][2];

void min_self(int& a, int b) { a = std::min(a, b); }

int main() {
	int n, T; scanf("%d %d", &n, &T);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].first);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].second);
	a[0] = {0, -1}; // a origem
	++n;
	auto prev = [&](int x) {
		return (x+n-1)%n;
	};
	auto next = [&](int x) {
		return (x+1)%n;
	};
	auto dist = [&](int x, int y) {
		if(x > y) return y + T - x;
		return y - x;
	};
	memset(dp, 0x3f, sizeof dp);
	dp[0][0][0][0] = 0;
	for(int sz = 0; sz < n; sz++) {
		for(int l = 0; l < n; l++) {
			int r = (l+sz)%n;
			for(int k = 0; k <= sz; k++) {
				if(std::min(dp[l][r][k][0], dp[l][r][k][1]) == 0x3f3f3f3f || l == next(r)) continue;
				
				int t = dp[l][r][k][0] + dist(a[prev(l)].first, a[l].first);
				min_self(dp[prev(l)][r][k+(t<=a[prev(l)].second)][0], t);

				t = dp[l][r][k][1] + dist(a[prev(l)].first, a[r].first);
				min_self(dp[prev(l)][r][k+(t<=a[prev(l)].second)][0], t);

				t = dp[l][r][k][0] + dist(a[l].first, a[next(r)].first);
				min_self(dp[l][next(r)][k+(t<=a[next(r)].second)][1], t);

				t = dp[l][r][k][1] + dist(a[r].first, a[next(r)].first);
				min_self(dp[l][next(r)][k+(t<=a[next(r)].second)][1], t);
			}
		}
	}

	int ans = 0;
	for(int k = 0; k <= n; k++)
		for(int l = 0; l <= n; l++)
			for(int r = 0; r <= n; r++)
				for(int b : {0, 1})
					if(dp[l][r][k][b] < 0x3f3f3f3f)
						ans = k;
	printf("%d\n", ans);
}