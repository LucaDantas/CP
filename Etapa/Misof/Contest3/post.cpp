#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150010;

vector<int> g[maxn], rg[maxn];

bool mark[maxn];

struct ANS
{
	int a, b, c;
};

vector<ANS> ans;

int dfs(int u, int p, int puxa) {
	mark[u] = 1;
	int ret = puxa<<1;
	for(int v : g[u])
		if(v == p) ret |= 1;
	vector<int> recebe, manda;
	for(int v : g[u]) {
		if(v == p) continue;
		int aq = dfs(v, u, 1);
		if(aq&1) recebe.push_back(v);
		if(aq&2) manda.push_back(v);
	}
	for(int v : rg[u]) {
		if(mark[v]) continue;
		int aq = dfs(v, u, 0);
		if(aq&1) recebe.push_back(v);
	}
	while(recebe.size() && manda.size()) {
		ans.push_back({recebe.back(), u, manda.back()});
		recebe.pop_back();
		manda.pop_back();
	}
	if(manda.size() && puxa) {
		ans.push_back({p, u, manda.back()});
		ret ^= 2;
	}
	if(recebe.size() && (ret&1)) {
		ret ^= 1;
		ans.push_back({recebe.back(), u, p});
	}
	return ret;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].push_back(b);
		rg[b].push_back(a);
	}
	for(int i = 1; i <= n; i++)
		if(!mark[i]) dfs(i, 0, 0);
	if(2*(int)ans.size() != m) return puts("No"), 0;
	puts("Yes");
	for(auto a : ans)
		printf("%d %d %d %d\n", a.a, a.b, a.b, a.c);
}