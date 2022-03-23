#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110, maxk = 1010, inf = 0x3f3f3f3f;

int valor[maxn][maxn]; // grafo completo final
int dist[maxn][maxn]; // floyd warshall

int b[maxn][maxk], s[maxn][maxk];

long long dp[maxn][maxn];

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	memset(dist, 0x3f, sizeof dist);
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			scanf("%d %d", &b[i][j], &s[i][j]);
	
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		dist[a][b] = w;
	}

	for(int l = 1; l <= n; l++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(dist[i][l] < inf && dist[l][j] < inf)
					dist[i][j] = min(dist[i][j], dist[i][l] + dist[l][j]);

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int l = 1; l <= k; l++)
				if(b[i][l] != -1 && s[j][l] != -1)
					valor[i][j] = max(valor[i][j], -b[i][l] +s[j][l]); // compro 'l' em 'i' e vendo em 'j'

	int ans = 0;

	int l = 0, r = inf;
	while(l <= r) {
		int x = (l+r) >> 1;
		
		memset(dp, 0x3f, sizeof dp);

		// quero achar o menor x tal que {media < x}, então a resposta é x-1

		// sum_valor / sum_dist < x ==> sum_valor - x * sum_dist < 0 ==>
		// sum_dist * x - sum_valor > 0 ==> agora o menor ciclo tem que ser maior que 0

		long long mn = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(dist[i][j] != inf) dp[i][j] = 1ll * dist[i][j] * x - valor[i][j];
		
		for(int l = 1; l <= n; l++)
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					dp[i][j] = min(dp[i][j], dp[i][l] + dp[l][j]);

		for(int i = 1; i <= n; i++)
			mn = min(mn, dp[i][i]);

		if(mn > 0) {
			ans = x-1; // resposta invalida, então a ultima valida é x-1 (assumindo que x já é o valor final)
			r = x-1;
		} else {
			l = x+1;
		}
	}

	printf("%d\n", ans);
}
