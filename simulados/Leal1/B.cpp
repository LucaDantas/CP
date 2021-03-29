#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int maxn = 1e5+10, B = 200;

vector<int> g[maxn];

bool busy[maxn], tem[maxn], seen[maxn];

int dp[maxn], ans[maxn];

vector<pii> maiores[maxn];

int dfs_dp(int u) {
	if(dp[u] != -1) return dp[u];
	tem[u] = !busy[u];
	int& ans = dp[u];
	ans = 0;
	for(int v : g[u])
		ans = max(ans, dfs_dp(v)+tem[v]), tem[u] |= tem[v];
	return ans;
}

void my_merge(int u, int v) {
	static vector<pii> result; result.clear();
	int ptr = 0;
	for(int i = 0; i < (int)maiores[u].size(); i++) {
		for(; ptr < (int)maiores[v].size() &&
			maiores[v][ptr].first >= maiores[u][i].first; ptr++)
			result.push_back({maiores[v][ptr].first+1, maiores[v][ptr].second});
		result.push_back(maiores[u][i]);
	}
	for(; ptr < (int)maiores[v].size(); ptr++)
		result.push_back({maiores[v][ptr].first+1, maiores[v][ptr].second});
	maiores[u].clear();
	for(pii p : result)
		if(!seen[p.second] && maiores[u].size() < B) maiores[u].push_back(p), seen[p.second] = 1;
	for(pii p : maiores[u])
		seen[p.second] = 0;
}

int main() {
	int n, m, Q; scanf("%d %d %d", &n, &m, &Q);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &b, &a), g[a].push_back(b);
	
	for(int u = 1; u <= n; u++) {
		maiores[u].push_back({0, u});
		for(int v : g[u])
			my_merge(u, v);
	}
	for(int q = 0; q < Q; q++) {
		int t, y; scanf("%d %d", &t, &y);
		vector<int> rm;
		for(int i = 0, x; i < y; i++)
			scanf("%d", &x), rm.push_back(x);
		sort(rm.begin(), rm.end());
		if(y >= B) {
			memset(dp, -1, sizeof dp);
			memset(busy, 0, sizeof busy);
			for(int x : rm)
				busy[x] = 1;
			printf("%d\n", dfs_dp(t)==0&&busy[t]?-1:dp[t]);
		} else {
			int ans = -1;
			for(pii p : maiores[t])
				if(!binary_search(rm.begin(), rm.end(), p.second))
					{ans = p.first; break;}
			printf("%d\n", ans);
		}
	}
}