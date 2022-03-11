#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 18;

vector<int> g[maxn];

long long dp[maxn][1<<maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		bool foi = 0;
		for(int j = 0; j < n; j++) {
			int x; scanf("%d", &x);
			--x;
			if(!foi) g[i].push_back(x);
			foi |= x == i;
		}
	}

	dp[0][0] = 1;
	for(int mask = 1; mask < (1<<n); mask++) {
		int lsb = 31-__builtin_clz(mask&-mask);
		for(int l = 0; l < n; l++) {
			if(l < lsb) continue;
			for(int v : g[l]) if((1<<v) & mask) {
				int new_mask = mask^(1<<v);
				if(v != lsb)
					dp[l][mask] += dp[v][new_mask];
				else
					dp[l][mask] += dp[31-__builtin_clz(new_mask&-new_mask)][new_mask];
			}
		}
	}

	int q; scanf("%d", &q);
	while(q--) {
		int mask = 0;
		
		char s[maxn]; scanf(" %s", s);

		for(int i = 0; i < n; i++)
			if(s[i] == 'H') mask ^= 1<<i;

		int comp = ((1<<n)-1)^mask;
		printf("%lld\n", dp[31-__builtin_clz(mask&-mask)][mask] * dp[31-__builtin_clz(comp&-comp)][comp]);
	}
}
