#include <cstdio>
#include <vector>
#include <bitset>

constexpr int maxv = 1e4+10, maxn = 105;

std::bitset<maxv> dp[maxn];

inline int sq(int x) { return x*x; }

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		std::vector<int> a(n), b(n);
		for(int& x : a)
			scanf("%d", &x);
		for(int& x : b)
			scanf("%d", &x);
		
		int soma = 0;
		std::vector<int> opa(n+1);
		for(int i = 0; i < n; i++) {
			if(a[i] < b[i]) std::swap(a[i], b[i]);
			opa[i+1] = a[i]-b[i];
			soma += opa[i+1];
		}
		
		dp[0].set(0);
		for(int i = 1; i <= n; i++)
			dp[i] = dp[i-1] | (dp[i-1] << opa[i]);

		int val = 0x3f3f3f3f, meio = soma/2;
		for(int i = meio; i <= soma; i++)
			if(dp[n][i]) { val = i; break; }
		for(int i = meio; i >= 0 && meio-i < val-meio; i--)
			if(dp[n][i]) { val = i; break; }

		for(int i = n; i >= 1; i--) {
			if(val >= opa[i] && dp[i-1].test(val - opa[i])) val -= opa[i]; // ele tá na resposta
			else std::swap(a[i-1], b[i-1]); // não ta na resposta
		}

		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = i+1; j < n; j++)
				ans += sq(a[i]+a[j]) + sq(b[i]+b[j]);

		printf("%d\n", ans);
	}
}
