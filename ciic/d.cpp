#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) (int)((a).size())
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 3e5+10;

int f[maxn], tipo[maxn], grau[maxn];

map<int, vector<int>> atv;

bool ok[5];

int sla(char c) {
	if(c == 'E') return 1;
	if(c == 'O') {
		ok[2] = 1;
		return 2;
	}
	if(c == 'A') {
		ok[3] = 1;
		return 3;
	}
	if(c == 'X') {
		ok[4] = 1;
		return 4;
	}
	// if(c == 'L')
	return 5;
}

vector<int> topBFS(int n) {
	queue<int> q;
	vector<int> ans;
	for(int i = 0; i < n; i++)
		if(tipo[i] == 1) q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop();
		ans.pb(u);
		--grau[f[u]];
		if(!grau[f[u]])
			q.push(f[u]);
	}
	return ans;
}

vector<int> liga[maxn];

void junta(vector<int>& a, vector<int>& b) {
	if(sz(a) < sz(b)) swap(a, b);
	for(int x : b)
		a.pb(x);
	b.clear();
}

bool mark[maxn];
int final[maxn], cnt[maxn], tot[maxn];

vector<int> ans[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		char c; scanf(" %c", &c);
		tipo[i] = sla(c);
	}
	for(int i = 0; i < n; i++) {
		int m; scanf("%d", &m);
		if(tipo[i] == 1) {
			liga[i] = {i};
			for(int j = 0, val; j < m; j++)
				scanf("%d", &val), atv[val].pb(i);
		} else if(tipo[i] == 5) {
			grau[i] = 1;
			int val; scanf("%d", &val);
			f[val] = i;
			f[i] = -1;
		} else {
			grau[i] = 2;
			int val; scanf("%d", &val);
			f[val] = i;
			scanf("%d", &val);
			f[val] = i;
		}
	}
	vector<int> top = topBFS(n);
	for(int i = 0; i < n; i++)
		if(f[i] != -1) junta(liga[f[i]], liga[i]);

	for(int i = 0; i < n; i++) {
		if(tipo[i] == 5) {
			for(int x : liga[i])
				final[x] = i;
			tot[i] = sz(liga[i]);
		}
	}

	// puts("XXXXX");

	for(auto aaa : atv) {
		// puts("AAAA");
		vector<int> pessoas = aaa.second;
		int tempo = aaa.first;

		vector<int> colocar;
		for(int x : pessoas) {
			++cnt[final[x]];
			if(!mark[final[x]]) mark[final[x]] = 1, colocar.pb(final[x]);
		}

		for(int x : colocar) {
			// fprintf(stderr, "%d %d\n", x, cnt[x]);
			if(ok[2]) {
				// or
				ans[x].pb(tempo);
			} else if(ok[4]) {
				if(cnt[x]&1) ans[x].pb(tempo);
			} else {
				if(cnt[x] == tot[x]) ans[x].pb(tempo);
			}
			cnt[x] = 0;
			mark[x] = 0;
		}
	}

	for(int i = 0; i < n; i++) {
		if(sz(ans[i]))
			for(int j = 0; j < sz(ans[i]); j++)
				printf("%d%c", ans[i][j], " \n"[j==sz(ans[i])-1]);
		else puts("");
	}
}