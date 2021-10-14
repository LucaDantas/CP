#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10;

int recebe[maxn][maxn][27];
vector<int> g[maxn][27], rg[maxn][27];

queue<pair<pair<int,int>,int>> q;

void dfs(int a, int b, int c) {
	if(c) {
		if(!g[b][c].size())
			q.push({{a, b}, c});
	} else {
		for(c=1; c <= 26; c++)
			for(int x : g[a][c])
				dfs(x, b, c);
	}
}

bool mark[maxn][maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b; char c; scanf("%d %d %c", &a, &b, &c);
		g[a][c-'a'+1].push_back(b);
		rg[b][c-'a'+1].push_back(a);
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dfs(i, j, 0);

	int ans = 0;

	while(q.size()) {
		int a = q.front().first.first, b = q.front().first.second;
		int c = q.front().second; q.pop();
		if(c == 0) {
			for(int pos = 1; pos <= 26; pos++) {
				for(int x : rg[b][pos])
					if(++recebe[a][x][pos] == (int)g[x][pos].size())
						q.push({{a, x}, pos});
			}
		} else {
			for(int x : rg[a][c])
				if(!mark[x][b])
					q.push({{x, b}, 0}), mark[x][b] = 1, ++ans;
		}
	}

	printf("%d\n", ans);
}
