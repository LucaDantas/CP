#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 18;

vector<int> g[maxn];

long long ans[1<<maxn]; // pra cada mask tem uma dp

long long dp[1<<maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		bool foi = 0;
		for(int j = 0; j < n; j++) {
			int x; scanf("%d", &x); --x;
			if(!foi) g[i].push_back(x);
			foi |= x == i;
		}
	}

	for(int mask = 0; mask < (1 << n); mask++) {
		int sz = __builtin_popcount(mask);
		
		for(int sub = (mask-1)&mask; sub > 0; sub = (sub-1) & mask)
			dp[sub] = 0;
		dp[0] = 0;

		dp[mask] = 1; // tem um jeito de fazer não colocando ninguém

		vector<int> opa;
		for(int i = 0; i < n; i++)
			if(mask & (1 << i)) opa.push_back(i);

		for(int sub = mask; sub > 0; sub = (sub-1) & mask) {
			int i = opa[__builtin_popcount(sub)-1]; // é o i-esimo cara de tras pra frente
			for(int v : g[i])
				if(sub & (1 << v)) dp[sub^(1<<v)] += dp[sub];
		}

		ans[mask] = dp[0];
	}

	int q; scanf("%d", &q);
	while(q--) {
		int mask = 0;
		
		char s[maxn]; scanf(" %s", s);

		for(int i = 0; i < n; i++)
			if(s[i] == 'H') mask ^= 1<<i;

		printf("%lld\n", ans[mask] * ans[((1<<n)-1)^mask]);
	}
}
