#include <stdio.h>

#define maxn 5010
#define mod 998244353

int dp[2][maxn];

int fat[maxn], inv_fat[maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void calc() {
	fat[0] = 1; inv_fat[0] = 1;
	for(int i = 1; i < maxn; i++) {
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv_fat[i] = power(fat[i], mod-2);
	}
}

int choose(int a, int b) {
	return (int)((1ll * fat[a] * inv_fat[b] % mod) * 1ll * inv_fat[a - b] % mod);
}

int main() {
	calc();
	int n, m; scanf("%d %d", &n, &m);
	dp[0][0] = 1;
	for(int i = 0; (1 << i) <= m; i++) {
		for(int qtd = 0; qtd <= n; qtd += 2) {
			for(int soma = 0; qtd * (1 << i) + soma <= m; soma++) {
				dp[1][qtd * (1 << i) + soma] += (int)(1ll * dp[0][soma] * choose(n, qtd) % mod);

				if(dp[1][qtd * (1 << i) + soma] >= mod)
					dp[1][qtd * (1 << i) + soma] -= mod;
			}
		}
		for(int soma = 0; soma <= m; soma++)
			dp[0][soma] = dp[1][soma], dp[1][soma] = 0;
	}
	printf("%d\n", dp[0][m]);
}