#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 1010

int tab[MAXN][MAXN], n, k;

int dp(int i, int p){
	if(i == n) return 1;
	if(tab[i][p] != -1) return tab[i][p];
	int coloca = (p)? (dp(i+1, p-1))%(1000000007) : 0;
	int nao_coloca = (dp(i+1, k))%(1000000007);
	return tab[i][p] = (coloca + nao_coloca)%(1000000007);
}

int main(){
	scanf("%d%d", &n, &k);
	k--;
	memset(tab, -1, sizeof tab);
	printf("%d\n", dp(0, k));
}
