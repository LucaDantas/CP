#include<bits/stdc++.h>
using namespace std;

#define MAXN 110
#define endl '\n'

int mapa[MAXN][MAXN];
int n, m, ships = 0;
int *tab[MAXN][MAXN];
int ans[MAXN*MAXN/2];

//NEGÓCIO FEIO DA PORRA MAS FDS
void dfs(int l, int c){
	if(mapa[l-1][c] == 1 && tab[l-1][c] == NULL){
		tab[l-1][c] = tab[l][c];
		++*(tab[l][c]);
		dfs(l-1,c);
	}
	if(mapa[l+1][c] == 1 && tab[l+1][c] == NULL){
		tab[l+1][c] = tab[l][c];
		++*(tab[l][c]);
		dfs(l+1,c);
	}
	if(mapa[l][c-1] == 1 && tab[l][c-1] == NULL){
		tab[l][c-1] = tab[l][c];
		++*(tab[l][c]);
		dfs(l,c-1);
	}
	if(mapa[l][c+1] == 1 && tab[l][c+1] == NULL){
		tab[l][c+1] = tab[l][c];
		++*(tab[l][c]);
		dfs(l,c+1);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	memset(mapa, 0, sizeof(mapa));
	memset(tab, 0, sizeof(tab));
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		for(int j = 1; j <= m; j++){
			if(s[j-1] != '.') mapa[i][j] = 1;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(mapa[i][j] == 1 && tab[i][j] == NULL){
				ans[ships] = 1;
				tab[i][j] = &ans[ships++];
				dfs(i,j);
			}
		}
	}
	int k, dest = 0;
	cin >> k;
	for(int i = 1; i <= k; i++){
		int l, c;
		cin >> l >> c;
		if(tab[l][c] != NULL) --*(tab[l][c]);
	}
	for(int i = 0; i < ships; i++){
		if(ans[i] == 0) dest++;
	}
	cout << dest << endl;
}
