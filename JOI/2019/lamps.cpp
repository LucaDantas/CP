#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

int a[maxn], b[maxn], dp[8], new_dp[8];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char c; scanf(" %c", &c);
		a[i] = c-'0';
	}
	for(int i = 1; i <= n; i++) {
		char c; scanf(" %c", &c);
		b[i] = c-'0';
	}
	auto get = [](int i, int mask) {
		int opa = a[i];
		if(mask&1) opa = 0;
		if(mask&2) opa = 1;
		if(mask&4) opa ^= 1;
		return opa;
	};
	for(int mask = 1; mask < 8; mask++)
		dp[mask] = n;
	for(int i = 1; i <= n; i++) {
		for(int mask = 0; mask < 8; mask++) {
			new_dp[mask] = n;
			if(get(i, mask) == b[i]) {
				for(int ant = 0; ant < 8; ant++) {
					new_dp[mask] = min(new_dp[mask], dp[ant] + __builtin_popcount(~ant&mask));
				}
			}
		}
		for(int mask = 0; mask < 8; mask++)
			swap(new_dp[mask], dp[mask]);
	}
	int ans = n;
	for(int mask = 0; mask < 8; mask++)
		ans = min(ans, dp[mask]);
	printf("%d\n", ans);
}