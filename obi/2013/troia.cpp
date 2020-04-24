#include<bits/stdc++.h>
using namespace std;

#define MAXN 50100

vector<int> node[MAXN];
int n, m;
bitset<MAXN> seen;

void dfs(int ind){
	for(int i = 0; i < (int)node[ind].size(); i++){
		if(seen.test(node[ind][i])) continue;
		seen.set(node[ind][i]);
		dfs(node[ind][i]);
	}
}

int main(){
	int ans = 0;
	scanf("%d%d", &n, &m);
	for(int i = 0, a, b; i < m; i++){
		scanf("%d%d", &a, &b);
		node[a].push_back(b);
		node[b].push_back(a);
	}
	for(int i = 1; i <= n; i++){
		if(seen.test(i)) continue;
		ans++;
		seen.set(i);
		dfs(i);
	}
	printf("%d\n", ans);
}
