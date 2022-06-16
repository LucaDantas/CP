// subtask da permutacao random ai
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 20010, mod = 1e9+7;

int paint[maxn][2];
int pot[maxn], dp[maxn];

void pre() {
	pot[0] = 1;
	for(int i = 1; i < maxn; i++)
		pot[i] = (int)(1ll * 26 * pot[i-1] % mod);
	dp[1] = 26; // todo mundo igual
	for(int i = 2; i < maxn; i++) {
		dp[i] = (int)(1ll * i * (i-1) / 2 % mod * pot[i-2] % mod);
		dp[i] += dp[i-1], dp[i] %= mod;
	}
}

int main() {
	pre();
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b, t = 0;
		scanf("%d %d", &a, &b);
		if(a > b)
			swap(a, b), t = 1;
		paint[a][t]++, paint[b+1][t]--;
		// t: 0 => color[group(a)] <= color[min(b, group(a)+1)], 1 => color[group(a)] >= color[min(b, group(a)+1)]
	}
	int ans = 1;
	int last = (paint[1][0]>0) | ((paint[1][1]>0)<<1), sz = 1; // cada bit representa se tem algo dessa cor
	printf("%d %d\n", 1, last);
	for(int i = 2; i <= n; i++) {
		paint[i][0] += paint[i-1][0];
		paint[i][1] += paint[i-1][1];

		int aq = (paint[i][0]>0) | ((paint[i][1]>0)<<1);
		printf("%d %d\n", i, aq);
		if(last == aq) ++sz;
		else {
			ans *= last == 0 ? pot[sz] : last == 3 ? 26 : dp[sz];
			ans %= mod;
			sz = 1;
			last = aq;
		}
	}
	// o ultimo grupo eu nao ajeitei ne
	ans *= last == 0 ? pot[sz] : last == 3 ? 26 : dp[sz];
	ans %= mod;
	printf("%d\n", ans);
}
