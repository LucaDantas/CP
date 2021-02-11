#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
#include<cassert>
#include<algorithm>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

vector<pair<int,int>> g[maxn], rev_g[maxn], query[maxn];

int K, dist[maxn][5], ans[maxn];

void min_self(int& a, int b) {a = min(a,b);}

void solve(int l, int r) {
	if(l == r) return;
	int m = (l+r) >> 1;
	solve(l, m); solve(m+1, r);

	for(int i = K*l; i < K*(r+1); i++)
		for(int j = 0; j < K; j++)
			dist[i][j] = inf;

	for(int x = K*m; x < K*(m+1); x++) {
		dist[x][x%K] = 0;
		queue<int> q;

		// andando pra esquerda
		q.push(x);
		while(q.size()) {
			int u = q.front(); q.pop();
			for(auto pp : rev_g[u]) {
				auto [v, w] = pp;
				if(dist[v][x%K] == inf) q.push(v);
				min_self(dist[v][x%K], dist[u][x%K] + w);
			}
		}

		// andando pra direita
		q.push(x);
		while(q.size()) {
			int u = q.front(); q.pop();
			for(auto pp : g[u]) {
				auto [v, w] = pp;
				if(dist[v][x%K] == inf) q.push(v);
				min_self(dist[v][x%K], dist[u][x%K] + w);
			}
		}
	}

	for(int i = K*l; i < K*(m+1); i++) {
		while(query[i].size() && query[i].back().first/K <= r) {
			auto [b, id] = query[i].back();
			query[i].pop_back();
			for(int x = 0; x < K; x++)
				min_self(ans[id], dist[i][x]+dist[b][x]);
		}
	}
}

int main() {
	int n, m, q; scanf("%d %d %d %d", &K, &n, &m, &q);
	for(int i = 0, a, b, c; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		g[a].push_back({b, c});
		rev_g[b].push_back({a, c});
	}
	for(int i = 0; i < q; i++) {
		int a, b; scanf("%d %d", &a, &b);
		query[a].push_back({b, i});
		ans[i] = inf;
	}
	for(int i = 0; i < n; i++)
		sort(query[i].begin(), query[i].end()), reverse(query[i].begin(), query[i].end());
	solve(0, (n-1)/K);
	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]<inf?ans[i]:-1);
}
