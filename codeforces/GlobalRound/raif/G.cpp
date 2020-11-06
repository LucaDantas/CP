#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e6+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

int f[6], pot[6];
ll dp[maxn];

int main() {
	for(int i = 1; i < maxn; i++)
		dp[i] = -inf;
	int k; scanf("%d", &k);
	for(int i = 0; i <= 5; i++) {
		scanf("%d", &f[i]);
		pot[i] = (i?pot[i-1]*10:1);
		for(int l = 0, sobra = 3*(k-1); sobra; l++) {
			int val = min(1 << l, sobra);
			sobra -= val;
			if(1ll*val*pot[i] >= 1ll*maxn) continue;
			for(int peso = (maxn - 1) - 3*val*pot[i]; peso >= 0; peso--)
				dp[peso + 3*val*pot[i]] = max(dp[peso + 3*val*pot[i]], dp[peso] + 1ll*val*f[i]);
		}
		for(int peso = maxn - 1; peso >= 0; peso--) {
			for(int x = 0; x <= 9; x++) {
				if(peso + x*pot[i] >= maxn) break;
				ll extra = x%3==0?1ll*f[i]*(x/3):0;
				dp[peso + x*pot[i]] = max(dp[peso + x*pot[i]], dp[peso] + extra);
			}
		}
	}

	int q; scanf("%d", &q);
	while(q--) {
		int x; scanf("%d", &x);
		printf("%lld\n", dp[x]);
	}
}