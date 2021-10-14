#include <bits/stdc++.h>
using namespace std;

constexpr int maxb = 23, maxn = 1<<maxb;

int a[32][32];

bool on(int mask, int b) { return (mask & (1 << b)) > 0;}

int st(int mask, int b) { return mask | (1 << b); }

void max_self(long long& a, long long b) { a = max(a, b); }

int n;
map<int,long long> dp;

long long solve(int mask) {
  if(dp.count(mask)) return dp[mask];
  int primeiro = 0;
  for(int i = 0; i < n; i++)
    if(!on(mask, i)) { primeiro = i; break; }
  long long here = 0;
  for(int j = primeiro+1; j < n; j++)
    if(!on(mask, j)) here = max(here, solve( mask|(1<<primeiro)|(1<<j) ) + a[primeiro][j]);
  return dp[mask] = here;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	dp[(1<<n)-1] = 0;
	printf("%lld\n", solve(0));
}
