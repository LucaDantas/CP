#include<bits/stdc++.h>
using namespace std;

#define MAXN 10100

int tab[MAXN];

void compute(int a){
	int raiz = (int)sqrt(a), last = 0;
	for(int i = 1; i <= raiz; i++){
		tab[a/i]++;
	}
	for(int i = raiz; i >= 1; i--){
		tab[i] += a/i - last;
		last = a/i;
	} 
}

int main(){
	int n, k, bigm = 0;
	scanf("%d%d", &n, &k);
	memset(tab, 0, sizeof tab);
	for(int i = 0, m; i < k; i++){
		scanf("%d", &m);
		bigm = max(bigm, m);
		compute(m);
	}
	for(int i = bigm; i > 0; i--){
		if(n <= tab[i]){
			printf("%d\n", i);
			break;
		}
		n -= tab[i];
	}
}
