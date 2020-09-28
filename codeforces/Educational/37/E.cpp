#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

#define pb push_back

set<int> s;

set<int> g[maxn];
vector<int> ans;

int mark[maxn];

queue<int> q;

int bfs() {
	int salvar = (int)s.size();
	s.erase(q.front());
	while(q.size()) {
		int u = q.front(); q.pop();
		static vector<int> apagar;
		mark[u] = 1;
		for(auto it : s)
			if(!g[u].count(it))
				q.push(it), apagar.pb(it);
		for(auto it : apagar)
		    s.erase(it);
		apagar.clear();
	}
	return salvar-(int)s.size();
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int u, v; scanf("%d %d", &u, &v); u--, v--;
		g[u].insert(v);
		g[v].insert(u);
	}
	for(int i = 0; i < n; i++)
		s.insert(i);
	for(int i = 0; i < n; i++)
		if(!mark[i]) q.push(i), ans.pb(bfs());
	printf("%d\n", (int)ans.size());
	sort(ans.begin(), ans.end());
	for(auto it : ans)
		printf("%d ", it);
	printf("\n");
}