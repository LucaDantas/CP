#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+100;

int n, m;

vector<int> g[maxn];

int ingrau[maxn];

vector<int> topBFS(){
	vector<int> ans;
	
	priority_queue<int, vector<int>, greater<int>> q;
	
	for(int i = 0; i < n; i++) if(ingrau[i] == 0) q.push(i);
	
	while(!q.empty()){
		int u = q.top();
		q.pop();
		
		ans.push_back(u);
		
		for(auto v : g[u]){
			ingrau[v]--;
			if(!ingrau[v]) q.push(v);
		}
	}
	
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v; scanf("%d %d", &u, &v);
		g[u].push_back(v);
		ingrau[v]++;
	}
	vector<int> ans = topBFS();
	if(ans.size() != n) puts("*");
	else for(int i=0; i<n; i++) printf("%d\n", ans[i]);
}
