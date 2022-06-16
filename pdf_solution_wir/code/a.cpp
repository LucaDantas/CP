#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int grau[maxn];

vector<int> g[maxn], vizinhos[maxn];
bool infected[maxn], mark[maxn];

int cost_kill[maxn], inf_strength[maxn];

void max_self(int& a, int b) { a = max(a, b); }

void clear(int n) {
	for(int i = 1; i <= n; i++) {
		grau[i] = g[i].size(), mark[i] = 0;
		cost_kill[i] = 0, inf_strength[i] = 0;
		vizinhos[i].clear();
	}
}

int aux[maxn];

pair<int,int> calc(const vector<int>& st) {
	int mx = 0, atv = 0;
	for(int x : st)
		aux[x]++, mx = max(mx, x);
	pair<int,int> ans = {0, 0};
	for(int i = 0; i < (int)(st.size()) && mx - i >= 0; i++) {
		atv += aux[mx - i];
		ans = max(ans, {mx - i + atv, atv});
	}
	for(int x : st)
		aux[x] = 0;
	return ans;
}

bool get(int n) {
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(grau[i] == 1) q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop();
		mark[u] = 1;
		int pos_kill = 0;
		tie(cost_kill[u], pos_kill) = calc(vizinhos[u]);
		
		int vizinho = -1;
		for(int v : g[u])
			if(!mark[v]) vizinho = v;

		if(vizinho == -1)
			return inf_strength[u] >= cost_kill[u];

		if(inf_strength[u] > cost_kill[u])
			max_self(inf_strength[vizinho], inf_strength[u]-1);
		else if(inf_strength[u] == cost_kill[u])
			max_self(inf_strength[vizinho], inf_strength[u] - pos_kill - 1);
		else
			vizinhos[vizinho].push_back(cost_kill[u]); // eu nao consigo me matar e preciso que o vizinho venha

		if(--grau[vizinho] == 1)
			q.push(vizinho);
	}
	assert(0);
	return 0;
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 0, a; i < k; i++)
		scanf("%d", &a), infected[a] = 1;
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	int l = 0, r = n, ans = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		clear(n);
		for(int i = 1; i <= n; i++)
			inf_strength[i] = infected[i] ? m : -1;
		if(get(n))
			ans = m, r = m-1;
		else
			l = m+1;
	}
	printf("%d\n", ans);
}
