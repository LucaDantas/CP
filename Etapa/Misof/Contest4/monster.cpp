#include <bits/stdc++.h>
using namespace std;

constexpr int maxk = 26, maxn = 5e5+10, logn = 22, p = 31, mod = 1e9+9;

int eat[maxk][maxk], a[maxn];
char str[maxn];

int dp[maxn][logn]; // salvo pra cada cara qual o hash dos logn pot2 proximos pais
int pai[maxn][logn]; // indice dos pais

bool comp(int x, int y) { // return dp[x] <= dp[y] ? 1 : 0;
	for(int l = logn-1; l >= 0; l--)
		if(dp[x][l] == dp[y][l])
			x = pai[x][l], y = pai[y][l]; // pai[x][l] é o primeiro cara não contado no hash de dp[x][l]
	return a[x] <= a[y]; // we know either a[x] != a[y] or the entire sequence is equal
}

vector<int> pos[maxk];

int pot[logn];

void calc() {
	pot[0] = p;
	for(int i = 1; i < logn; i++)
		pot[i] = (int)(1ll * pot[i-1] * pot[i-1] % mod); // potencias de potencias de 2 de p
}

int main() {
	calc();

	int k, n; scanf("%d %d", &k, &n);
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < k; j++) {
			char c; scanf(" %c", &c), eat[i][j] = c-'0';
		}
	}

	scanf(" %s", str);
	for(int i = 0; i < n; i++)
		a[i] = str[i]-'a';

	{
		// base da dp de n
		a[n] = -1; // coloco -1 pra simbolizar vazio, melhor que todas as letras
		for(int l = 0; l < logn; l++)
			pai[n][l] = n; // como eu sou o último eu aponto pra mim mesmo
			// não encho o vetor dp[n][l] porque ele é tudo 0 mesmo
	}

	vector<int> melhores = {n}, st = {n};
	for(int i = n-1; i >= 0; i--) {
		while(st.back() != n && eat[a[i]][a[st.back()]])
			st.pop_back();

		// assim eu sei qual a ultima posicao que eu consigo comer e chegar
		int last = st.back();

		st.push_back(i);

		auto prox = --upper_bound(melhores.rbegin(), melhores.rend(), last);

		pai[i][0] = *prox; // *prox é o id do proximo cara que inicia a melhor sequencia partindo de mim
		for(int l = 1; l < logn; l++)
			pai[i][l] = pai[pai[i][l-1]][l-1];

		for(int l = 0; l < logn; l++)
			dp[i][l] = ((1ll*dp[pai[i][0]][l]*p%mod - 1ll*(a[pai[i][l]]+1)*pot[l]%mod + mod)%mod + (a[i]+1)) % mod;

		while(comp(i, melhores.back())) // deixo só os caras bons ativos (pareto)
			melhores.pop_back();
		melhores.push_back(i);
	}

	int pos = 0;
	while(pos < n)
		printf("%c", (char)(a[pos]+'a')), pos = pai[pos][0];
	puts("");
}
