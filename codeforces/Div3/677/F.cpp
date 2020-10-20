#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 80;
constexpr int inf = 0x3f3f3f3f;

int dp[maxn][maxn];

inline void max_self(int& a, int b) {a = max(a, b);}

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < maxn; i++)
		for(int j = 0; j < maxn; j++)
			dp[i][j] = -inf;
	dp[0][0] = 0;
	while(n--) {
		for(int i = 0; i < m; i++) {
			int v; scanf("%d", &v);
			for(int j = m/2; j >= 0; j--)
				for(int mod = 0; mod < k; mod++)
					max_self(dp[j+1][(mod+v)%k], dp[j][mod] + ((mod+v)/k));
		}
		for(int mod = 0; mod < k; mod++) {
			for(int j = 0; j <= m/2; j++)
				max_self(dp[0][mod], dp[j][mod]);
		}
	}
	printf("%d\n", dp[0][0]*k);
}