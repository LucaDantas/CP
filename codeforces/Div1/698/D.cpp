#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 5e5+10;

vector<int> g[maxn], g2[maxn], grp[maxn];

set<int> st;

bool mark[maxn];

int p[maxn], q[maxn], ptr = 1;

void dfs(int u) {
	vector<int> rm;
	for(int x : st)
		if(!binary_search(g[u].begin(), g[u].end(), x))
			rm.pb(x);
	for(int x : rm)
		st.erase(x);
	for(int x : rm)
		g2[u].pb(x), g2[x].pb(u), dfs(x);
}

bool dfs2(int u) {
	mark[u] = 1;
	bool ok = 0;
	for(int v : g2[u])
		if(!mark[v] && !dfs2(v))
			ok = 1, grp[u].pb(v);
	return ok;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++)
			g[i].clear(), g2[i].clear(), grp[i].clear(), mark[i] = 0;

		for(int i = 0, a, b; i < m; i++)
			scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
		for(int i = 1; i <= n; i++)
			sort(g[i].begin(), g[i].end()), st.insert(i);
		
		for(int i = 1; i <= n; i++)
			if(st.count(i))
				st.erase(i), dfs(i);

		for(int i = 1; i <= n; i++)
			if(!g2[i].size())
				p[i] = q[i] = ptr++;
			else if(!mark[i] && !dfs2(i))
				grp[g2[i][0]].pb(i);


		for(int i = 1; i <= n; i++) {
			if(grp[i].size()) {
				p[i] = ptr;
				for(int v : grp[i])
					q[v] = ptr, p[v] = ++ptr;
				q[i] = ptr++;
			}
		}

		for(int i = 1; i <= n; i++)
			printf("%d ", p[i]);
		printf("\n");
		for(int i = 1; i <= n; i++)
			printf("%d ", q[i]);
		printf("\n");

		ptr = 1;
		st.clear();
	}
}