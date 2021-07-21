#include <cstdio>
#include <algorithm>

constexpr int maxn = 8010;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int a[maxn], b[maxn], f[maxn], n;
long long dp[maxn][maxn], aux[maxn];

inline long long max(long long a, long long b) { return a > b ? a : b; }
inline long long min(long long a, long long b) { return a < b ? a : b; }

int main() {
	scanf("%d", &n);
	a[0] = 0x3f3f3f3f;
	long long sum = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]), b[i] = a[i];

		sum += a[i];
		dp[i][1] = max(dp[i-1][1], a[i]);	
	}

	for(int i = 1; i <= n; i++)
		dp[0][i] = inf;
	std::sort(b+1, b+n+1);

	for(int k = 2; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			f[i] = i-1;
			aux[i] = inf;

			while(a[i] > a[f[i]])
				aux[i] = min(aux[i], aux[f[i]]), f[i] = f[f[i]];

			dp[i][k] = min(min(aux[i], dp[f[i]][k-1]) + a[i], dp[f[i]][k]);
			
			aux[i] = min(aux[i], dp[i][k-1]);
		}
	}
	long long opa[n+1];
	for(int i = 1; i <= n; i++) opa[i] = sum, sum -= b[i];
	std::reverse(opa+1, opa+1+n);
	for(int i = 1; i <= n; i++)
		printf("%lld %lld\n", dp[n][i], opa[i]);
}
