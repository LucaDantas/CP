#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

mt19937_64 rng(random_device{}());

constexpr int maxn = 4110;

int a[maxn][maxn], m;
ull w[maxn], peso[maxn][5], tudo[maxn], soma_pesos; // sum of the row

int val(char c) {
	if(c == 'A') return 1;
	if(c == 'C') return 2;
	if(c == 'G') return 3;
	return 4; // c == 'T'
}

int main() {
	int n, k; scanf("%d %d %d", &n, &m, &k);
	k = m-k;
	for(int i = 0; i < n; i++) {
		char s[maxn]; scanf(" %s", s);
		for(int j = 0; j < m; j++) {
			a[i][j] = val(s[j]); // estou codando para o caso onde só existem as letras A e C
		}
	}

	for(int i = 0; i < n; i++) // defino o peso de cada coluna
		w[i] = (ull) rng(), soma_pesos += w[i];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			peso[j][a[i][j]] += w[i];

	for(int i = 0; i < n; i++) {
		ull aq = 0;
		for(int j = 0; j < m; j++)
			aq += peso[j][a[i][j]] - w[i];

		bool ans = aq == (soma_pesos - w[i]) * k;

		if(ans) return printf("%d\n", i+1), 0;
	}
}
