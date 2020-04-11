#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

#define MAXN 100100
#define MAXT 262144 //2^18 > 2*MAXN

//ESSE CÓDIGO FICOU MUITO BUGADO E EU N SEI FAZER SEGMENT TREE DIREITO
//TA DANDO RUNTIME ERRO ENTÃO VOU FAZER OUTRA COM O CONCEITO DE FENWICK TREE

int n, m;
int value[MAXN], ans[15];
int tree[MAXT][15];

void build(int node, int i, int j){
	if(i==j){
		tree[node/2][value[i]]++;
		tree[node][value[i]] = 1;
	}
	int left = 2*node;
	int right = 2*node + 1;
	int mid = (i+j)/2;
	
	build(left, i, mid);
	build(right, mid+1, j);
	if(node == 1) return;
	for(int k = 0; k <= 9; k++){
		tree[node/2][k] += tree[node][k];
	}
}

void query(int node, int i, int j, int a, int b){
	if(a <= i && j <= b){
		for(int k = 1; k <= 9; k++){
			ans[k] += tree[node][k];
		}
		return;
	}
	if(i > b || a > j) return;
	int left = 2*node;
	int right = 2*node + 1;
	int mid = (i+j)/2;
	query(left, i, mid, a, b);
	query(right, mid+1, j, a, b);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> value[i];
	}
	build(1, 1, n);
	int cur, last;
	cin >> cur;
	for(int i = 1; i < m; i++){
		last = cur;
		cin >> cur;
		if(last >= cur) query(1, 1, n, cur, last);
		else query(1, 1, n, last, cur);
	}
	for(int i = 0; i <= 9; i++){
		cout << ans[i] << endl;
	}
}
