#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

pair<int,int> g[maxn];
bool mark[maxn];

int sz;

void dfs(int u) {
	mark[u] = 1;
	++sz;
	if(!mark[g[u].first]) dfs(g[u].first);
	if(!mark[g[u].second]) dfs(g[u].second);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].first = b;
		g[b].first = a;
	}

	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].second = b;
		g[b].second = a;
	}

	int cnt = 0;
	for(int i = 0; i < (n << 1); i++) {
		if(!mark[i]) dfs(i);
		if(sz > 2) ++cnt;
		sz = 0;
	}

	putchar('1');
	for(int i = 0; i < cnt; i++) putchar('0');
	putchar('\n');
}
