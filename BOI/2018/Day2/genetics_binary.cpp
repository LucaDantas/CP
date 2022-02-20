#include <bits/stdc++.h>
using namespace std;

using ull = long long;

mt19937 rng(random_device{}());

constexpr int maxn = 4110;

int a[maxn][maxn], m;
ull w[maxn], modified[maxn][maxn], tudo[maxn], soma_pesos; // sum of the row

ull dot(int x[], ull y[]) {
	ull ans = 0;
	for(int i = 0; i < m; i++)
		ans += x[i] * y[i];
	return ans;
}

int main() {
	int n, k; scanf("%d %d %d", &n, &m, &k);
	k = m - 2*k; // k vira k'
	for(int i = 0; i < n; i++) {
		char s[maxn]; scanf(" %s", s);
		for(int j = 0; j < m; j++) {
			a[i][j] = s[j] == 'A' ? 1 : -1; // estou codando para o caso onde só existem as letras A e C
		}
	}

	for(int i = 0; i < n; i++) // defino o peso de cada coluna
		w[i] = (ull) rng(), soma_pesos += w[i];

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			modified[i][j] = (ull) a[i][j] * w[i], tudo[j] += modified[i][j];
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			tudo[j] -= modified[i][j];
		
		bool ans = dot(a[i], tudo) == (soma_pesos - w[i]) * k;

		for(int j = 0; j < m; j++)
			tudo[j] += modified[i][j];

		if(ans) return printf("%d\n", i+1), 0;
	}
}
