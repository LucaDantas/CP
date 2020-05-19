#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
int tab[MAXN][MAXN];
vector<int> a, b;
int n, m;

int dp(int l, int r){
	if(l == n || r == m) return 0;
	if(tab[l][r] != -1) return tab[l][r];
	int coloca = 0, esq, dir;
	if(a[l] == b[r]) coloca = 1 + dp(l+1, r+1);
	esq = dp(l+1, r);
	dir = dp(l, r+1);
	return tab[l][r] = max(coloca, max(esq, dir));
}

int main(){
	scanf("%d%d", &n, &m);
	a.resize(n);
	b.resize(m);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < m; i++){
		scanf("%d", &b[i]);
	}
	memset(tab, -1, sizeof tab);
	int ans = dp(0,0);
	printf("%d %d\n", n-ans, m-ans);	
	return 0;
}
