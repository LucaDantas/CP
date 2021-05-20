#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10, maxp = 3e4+10;

int dp[maxn][maxp], dp2[maxp], peso[maxn], valor[maxn], ans[maxn], pos[maxn];

struct Query
{
	int b, c;
} query[maxn];

int main() {
	int n, r; scanf("%d %d", &n, &r);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &peso[i], &valor[i]);
	for(int i = 1, a, b, c; i <= n; i++) {
		scanf("%d %d %d", &a, &b, &c), query[i] = {b, c}, pos[i] = a;
	}
	for(int sla = n; sla >= 1; sla--) {
		int i = pos[sla];
		for(int p = r; p >= 0; p--)
			dp[sla][p] = max(dp[sla+1][p], (p >= peso[i]?dp[sla+1][p - peso[i]] + valor[i] : 0));
	}
	for(int sla = 1; sla <= n; sla++) {
		int i = pos[sla];
		peso[i] = query[sla].b;
		valor[i] = query[sla].c;
		for(int p = r; p >= peso[i]; p--)
			dp2[p] = max(dp2[p], dp2[p - peso[i]] + valor[i]);
		for(int j = 0; j <= r; j++)
			ans[sla] = max(ans[sla], dp[sla+1][j] + dp2[r - j]);
	}
	printf("%d\n", dp[1][r]);
	for(int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
}