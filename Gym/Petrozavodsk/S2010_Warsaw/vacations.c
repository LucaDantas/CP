// Link for this problem: http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=001366
// dpzinha nk⁵ agradavel

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <stdio.h>

#define maxn 210
#define maxk 12

int dp[2][maxk][maxk][maxk][maxk][maxk], a[3*maxn];
int min(int a, int b) { return a < b ? a : b; }
void max(int *a, int b) { if(*a < b) *a = b; }

FILE *in, *out;

int main() {
	in = fopen("h.in", "r");
	out = fopen("h.out", "w");
	int n, k; fscanf(in, "%d %d", &n, &k);
	for(int i = 0; i < 3*n; i++)
		fscanf(in, "%d", &a[i]);
	int ans = 0;
	for(int i = n-1; i >= 0; i--) {
		for(int pref = 0; pref <= k; pref++) {
			for(int d1 = 0; d1 <= k; d1++) {
				for(int d2 = 0; d2 <= k; d2++) {
					for(int qtd1 = 0; d1+qtd1 <= k; qtd1++) {
						for(int qtd2 = 0; d2+qtd2 <= k; qtd2++) {
							dp[0][pref][d1][d2][qtd1][qtd2] = 0;
							for(int mask = 0; mask < (1 << 3); mask++) {
								static int v[3], val; val = 0;
								for(int j = 0; j < 3; j++) v[j] = (mask&(1<<j)) > 0, val += a[i + j*n] * v[j];
								if(pref-v[0] < 0 || k-qtd1-v[1] < 0 || d1-v[1] < 0 || k-qtd2-v[2] < 0)
									continue;
								max(&dp[0][pref][d1][d2][qtd1][qtd2], val +
									dp[1][min(pref-v[0], k-qtd1-v[1])][min(d1-v[1], k-qtd2-v[2])]
									[d2-v[2]][qtd1+v[1]][qtd2+v[2]]);
								
								max(&ans, dp[0][pref][d1][d2][qtd1][qtd2]);
							}
						}
					}
				}
			}
		}

		for(int pref = 0; pref <= k; pref++)
			for(int d1 = 0; d1 <= k; d1++)
				for(int d2 = 0; d2 <= k; d2++)
					for(int qtd1 = 0; d1+qtd1 <= k; qtd1++)
						for(int qtd2 = 0; d2+qtd2 <= k; qtd2++)
							dp[1][pref][d1][d2][qtd1][qtd2] = dp[0][pref][d1][d2][qtd1][qtd2];
	}
	fprintf(out, "%d\n", ans);
}
