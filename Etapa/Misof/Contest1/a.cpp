#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10, maxc = 2510;

int cor[maxn][maxn];

bool markX[maxn], markY[maxn];

set<int> X, Y;

int cnt[maxn][maxc][2], qtd[maxn][2];

bool mark[maxn][maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &cor[i][j]);
			
			if(!cnt[i][cor[i][j]][0])
				++qtd[i][0];
			++cnt[i][cor[i][j]][0];

			if(!cnt[j][cor[i][j]][1])
				++qtd[j][1];
			++cnt[j][cor[i][j]][1];
		}
	}

	queue<pair<int,int>> q;
	for(int i = 0; i < n; i++)
		if(qtd[i][0] == 1) q.push({i, 0});
	for(int i = 0; i < m; i++)
		if(qtd[i][1] == 1) q.push({i, 1});

	while(q.size()) {
		int pos = q.front().first;
		int tipo = q.front().second;
		q.pop();

		if(!tipo) {
			for(int i = 0; i < m; i++) {
				if(mark[pos][i]) continue;
				mark[pos][i] = 1;
				if(cnt[i][cor[pos][i]][1] == 1)
					--qtd[i][1];
				--cnt[i][cor[pos][i]][1];
				if(qtd[i][1] == 1) q.push({i, 1});
			}
		} else {
			for(int i = 0; i < n; i++) {
				if(mark[i][pos]) continue;
				mark[i][pos] = 1;
				if(cnt[i][cor[i][pos]][0] == 1)
					--qtd[i][0];
				--cnt[i][cor[i][pos]][0];
				if(qtd[i][0] == 1) q.push({i, 0});
			}
		}
	}

	bool ok = 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			ok &= mark[i][j];
	puts(ok ? "real" : "fake");
}