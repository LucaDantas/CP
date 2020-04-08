#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define INF 1e9 + 100
vector<int> v;
int tab[MAXN][MAXN], n;

int dp(int i, int last){
	if(i == n+1) return 0;
	if(tab[i][last] != -1) return tab[i][last];
	int coloca = (v[last] <= v[i])? 1+dp(i+1, i) : 0;
	int nao_coloca = dp(i+1, last);
	return tab[i][last] = max(coloca,nao_coloca);
}

int main(){
	scanf("%d", &n);
	v.resize(n+1);
	memset(tab, -1, sizeof tab);
	v[0] = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
	}
	printf("%d\n", dp(1,0));
}
