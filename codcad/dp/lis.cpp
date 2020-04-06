#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define INF 10000
vector<int> v;
int tab[MAXN][MAXN], n;

int dp(int i, int k){
	if(k == 0) return 0;
	if(n-i < k) return INF;
	if(tab[i][k] != -1) return tab[i][k];
	int coloca = (v[i] <= dp(i+1, k-1))? max(v[i], dp(i+1, k-1)) : INF;
	int nao_coloca = dp(i+1, k);
	return min(coloca, nao_coloca);
}

int main(){
	scanf("%d", &n);
	v.resize(n);
	memset(tab, -1, sizeof tab);
	for(int i = 0; i < n; i++){
		scanf("%d", &v[i]);
	}
	int i = n;
	while(i > 0){
		printf("%d\n", dp(0,i));
		if(dp(0,i) < INF){
			printf("%d\n", i);	
			break;
		}
		i--;
	}
	if(i == 0) 
		printf("%d\n", i);
}
