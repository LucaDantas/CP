#include<bits/stdc++.h>
using namespace std;

/*
	Mesma solução de tfg
	dp[used][on][t]
	
	t == 0 -> não coloco o cara agora mas eu posso ou comecar a colocar
	com ele ou pular para o seguinte, se eu cheguei no caso on == n significa que
	todo mundo já passou então eu retorno 0
	
	t == 1 -> estou colocando o cara agora, se eu cheguei no último cara pra colocar
	e eu já usei todo mundo antes dele eu retorno 1, porque eu só tenho a opção de
	colocar ele. Se eu não tiver no último / não usado todo mundo, eu tenho a opção
	de colocar algum cara menor que eu (posso escolher qualquer um dos l[on]-used caras)
	o que aumenta o used mas eu continuo como sendo o maior atual, eu também posso
	simplesmente me colocar e partir para o próximo maior ser r[on], porque ele é o primeiro
	cara que pode entrar já que todos têm que ser maior que 2*eu
*/

constexpr int maxn = 5e3+10;
constexpr int mod = 998244353;

int n, dp[maxn][maxn][2], a[maxn], l[maxn], r[maxn];

int solve(int used, int on, int t) {
	int& ans = dp[used][on][t];
	if(ans != -1) return ans;
	ans = 0;
	if(!t) {
		if(on == n)
			return ans;
		return ans = ((solve(used, on+1, 0) + solve(used, on, 1)) % mod);
	} else {
		if(on == n-1 && used == n-1)
			return ans = 1;
		int choices = l[on] - used;
		if(choices > 0)
			ans = (int)(1ll*choices*solve(used+1, on, 1)%mod);
		return ans = (ans + solve(used+1, r[on], 0))%mod;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a+n);
	for(int i = 0, j = 0, k = 0; i < n; i++) {
		while(j < n && a[i] >= 2*a[j])
			j++;
		while(k < n && a[k] < 2*a[i])
			k++;
		l[i] = j, r[i] = k;
	}
	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(0, 0, 0));
}