#include<vector>
#include<algorithm>

#define sz(a) (int)(a.size())

int vencedorPartida(int a, int b);
int numeroVitorias(int competidor);
void responde(int tamanho, int array[]);

int saida[1001];
std::pair<int,int> qtd[1001];

void sub1(int n) {
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++)
			saida[vencedorPartida(i, j)-1]++;
	responde(n, saida);
}

void sub2(int n) {
	std::vector<int> ord = {1};
	for(int i = 2; i <= n; i++) {
		int l = 0, r = sz(ord)-1, pos = sz(ord);
		while(l <= r) {
			int m = (l+r) >> 1;
			if(vencedorPartida(i, ord[m]) == i) pos = m, r = m-1;
			else l = m+1;
		}
		std::vector<int> aux;
		for(int j = 0; j < pos; j++)
			aux.push_back(ord[j]);
		aux.push_back(i);
		for(int j = pos; j < sz(ord); j++)
			aux.push_back(ord[j]);
		ord = aux;
	}
	for(int i = 0; i < n; i++)
		saida[ord[i]-1] = n-i-1;
	responde(n, saida);
}

void sub4(int n) {
	int bom = 1;
	for(int i = 2; i <= n; i++)
		if(vencedorPartida(bom, i) == i) bom = i;
	bool ok = 1;
	for(int i = 1; i <= n; i++)
		if(i != bom && vencedorPartida(bom, i) == i) ok = 0;
	if(ok) saida[0] = bom;
	responde(ok, saida);
}

int vidas[1001];

void sub5(int n) {
	std::vector<int> gudi, real_gudi;
	for(int i = 1; i <= n; i++)
		vidas[i] = 5;
	for(int i = 1; i <= n; i++) {
		if(!vidas[i]) continue;
		for(int j = i+1; j <= n; j++) {
			if(!vidas[j]) continue;
			--vidas[i], --vidas[j];
			++vidas[vencedorPartida(i, j)];
			if(!vidas[i]) break;
		}
		if(vidas[i]) gudi.push_back(i);
	}
	for(int i = 0; i < sz(gudi); i++) {
		int u = gudi[i];
		vidas[u] = 5;
		for(int j = 1; j <= n; j++) {
			if(j != u && vencedorPartida(u, j) == j) --vidas[u];
			if(!vidas[u]) break;
		}
		if(vidas[u]) real_gudi.push_back(u);
	}
	for(int i = 0; i < sz(real_gudi); i++)
		saida[i] = real_gudi[i];
	responde(sz(real_gudi), saida);
}

void sub6(int N) {
	for(int i = 1; i <= N; i++)
		qtd[i] = {numeroVitorias(i), i};
	std::sort(qtd+1, qtd+N+1);
	for(int i = N; i >= 1; i--) {
		if(qtd[i].first == i-1) continue;
		std::vector<int> resultado(i);
		int l = -1;
		for(int j = i-1; j >= 1; j--)
			if(vencedorPartida(qtd[i].second, qtd[j].second) == qtd[j].second) l = j, resultado[j] = 1;
		for(int j = i-1; j >= 1; j--) {
			if(j != l && !resultado[j] && vencedorPartida(qtd[l].second, qtd[j].second) == qtd[j].second) {
				saida[0] = qtd[i].second, saida[1] = qtd[j].second, saida[2] = qtd[l].second;
				responde(3, saida);
				return;
			}
		}
	}
}

void processaTorneio(int S, int N) {
	if(S == 1) sub1(N);
	if(S == 2) sub2(N);
	if(S == 3 || S == 4) sub4(N);
	if(S == 5) sub5(N);
	if(S == 6) sub6(N);
}
