#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		std::vector<std::vector<int>> c(n<<1, std::vector<int>(n<<1));
		for(int i = 0; i < (n<<1); i++)
			for(int j = 0; j < (n<<1); j++)
				scanf("%d", &c[i][j]);
		long long ans = 0;
		for(int i = n; i < (n<<1); i++)
			for(int j = n; j < (n<<1); j++)
				ans += c[i][j];
		printf("%lld\n", ans + std::min({c[n][n-1], c[n-1][n], c[(n<<1)-1][n-1], c[n-1][(n<<1)-1], c[0][n], c[n][0], c[0][(n<<1)-1], c[(n<<1)-1][0]}));
	}
}
