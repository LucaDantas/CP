#include <cstdio>
#include <vector>

constexpr int maxn = 1e5+10, mod = 998244353;

int n, L[55], R[55], M, dp[2][maxn], mob[maxn], f[maxn];

std::vector<int> pr;

void sieve() {
	f[1] = mob[1] = 1;
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i, mob[i] = -1, pr.push_back(i);
		for(int j = 0; pr[j] < f[i] && pr[j] * i < maxn; j++)
			f[i * pr[j]] = pr[j], mob[i * pr[j]] = mob[i] * -1;
		if(1ll * i * f[i] < maxn) f[i * f[i]] = f[i], mob[i * f[i]] = 0;
	}
}

int solve(int mult) {
	int m = M / mult;
	for(int i = 0; i <= m; i++)
		dp[0][i] = dp[1][i] = 0;
	dp[1][0] = 1;
	auto itv = [](int k, int il, int ir) {
		if(ir < 0) return 0;
		return dp[k][ir] - (il <= 0 ? 0 : dp[k][il-1]);
	};
	for(int i = 0; i < n; i++) {
		int l = (L[i]+mult-1) / mult, r = R[i] / mult;
		if(l > r) return 0;
		for(int j = 0; j <= m; j++)
			dp[i&1][j] = (itv((i+1)&1, j-r, j-l) + (j ? dp[i&1][j-1] : 0)) % mod;
	}
	int ans = 0;
	for(int j = 0; j <= m; j++)
		ans = (ans + dp[(n-1)&1][j]) % mod;
	return ans;
}

int main() {
	sieve();
	scanf("%d %d", &n, &M);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &L[i], &R[i]);
	int ans = 0;
	for(int i = 1; i <= M; i++)
		ans = (ans + solve(i) * mob[i]) % mod;
	printf("%d\n", (ans+mod)%mod);
}
