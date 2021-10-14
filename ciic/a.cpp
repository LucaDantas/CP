#include <bits/stdc++.h>
using namespace std;

constexpr int maxb = 23, maxn = 1<<maxb;

long long dp[maxn];

int a[32][32];

bool on(int mask, int b) { return (mask & (1 << b)) > 0;}

int st(int mask, int b) { return mask | (1 << b); }

void max_self(long long& a, long long b) { a = max(a, b); }

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(int mask = 0; mask < (1 << n) - 1; mask++) {
		if(__builtin_popcount(mask)&1) continue;
		int primeiro = 0;
		for(int i = 0; i < n; i++)
			if(!on(mask, i)) { primeiro = i; break; }
		for(int i = primeiro + 1; i < n; i++)
			if(!on(mask, i)) max_self(dp[st(st(mask,primeiro),i)], dp[mask] + a[primeiro][i]);
	}
	printf("%lld\n", dp[(1<<n)-1]);
}