#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

char s[maxn];

int lascado[maxn]; // quantas letras sao diferentes

vector<int> quebra[maxn], apaga[maxn];

bool mark[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	scanf(" %s", s);
	for(int i = 0; i < n; i++) {
		int k; scanf("%d", &k);
		for(int j = 0; j < k; j++) {
			int a; char c; scanf("%d %c", &a, &c); --a;
			if(s[a] != c) ++lascado[i], quebra[a].push_back(i);
			else apaga[i].push_back(a);
		}
	}
	queue<int> q;
	for(int i = 0; i < n; i++)
		if(!lascado[i]) q.push(i);

	vector<int> ans;
	while(q.size()) {
		int u = q.front(); q.pop();
		ans.push_back(u);

		for(int c : apaga[u]) {
			while(quebra[c].size()) {
				if(!(--lascado[quebra[c].back()]))
					q.push(quebra[c].back());
				quebra[c].pop_back();
			}
			mark[c] = 1;
		}
	}

	bool ok = 1;
	for(int i = 0; i < m; i++)
		ok &= mark[i];
	
	if(!ok) return puts("-1"), 0;

	for(int x : ans)
		printf("%d ", x+1);
	puts("");
}
