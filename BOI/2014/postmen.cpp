#include<cstdio>
#include<vector>
#include <cassert>
#include<utility>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())

constexpr int maxn = 5e5+10;

vector<pair<int,int>> g[maxn];
vector<int> st;

bool mark[maxn], mark_edge[maxn];

int rd() {
	int result = 0;
	char ch;
	ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	return result;
}

void dfs(int i) {
	st.pb(i);
	while(1) {
		int u = st.back();
		mark[u] = 1;

		while(g[u].size() && mark_edge[g[u].back().second])
			g[u].pop_back();

		if(!sz(g[u])) break;

		int v = g[u].back().first;
		mark_edge[g[u].back().second] = 1;
		g[u].pop_back();

		if(mark[v]) {
			printf("%d", v);
			while(st.size() && st.back() != v) {
				printf(" %d", st.back());
				mark[st.back()] = 0;
				st.pop_back();
			}
			printf("\n");
		}
		else st.pb(v);
	}
	mark[i] = 0;
	st.clear();
}

int main() {
	int n = rd(), m = rd();
	for(int i = 0, a, b; i < m; i++)
		a=rd(), b=rd(), g[a].pb({b, i}), g[b].pb({a, i});
	for(int i = 1; i <= n; i++)
		dfs(i);
}