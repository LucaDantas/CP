#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using pil = pair<int,long long>;

#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())

constexpr int maxn = 250010, logn = 20;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int in[maxn], t;
long long ans[maxn], depth_euler[maxn];

vector<pii> g2[maxn];

vector<pil> virtual_g[maxn];
long long cost[maxn];

struct LCAA
{
	int pai[maxn][logn], real_depth[maxn];
	void euler(int u) {
		in[u] = ++t;
		for(int l = 1; l < logn; l++)
			pai[u][l] = pai[pai[u][l-1]][l-1];

		for(auto [v, w] : g2[u]) if(v != pai[u][0])
			pai[v][0] = u, depth_euler[v] = depth_euler[u]+w, real_depth[v] = real_depth[u]+1, euler(v);
	}

	int lca(int a, int b) {
		if(real_depth[a] < real_depth[b]) swap(a, b);
		for(int l = logn-1; l >= 0; l--)
			if(real_depth[a] - (1 << l) >= real_depth[b]) a = pai[a][l];
		if(a == b) return a;
		for(int l = logn-1; l >= 0; l--)
			if(pai[a][l] != pai[b][l]) a = pai[a][l], b = pai[b][l];
		return pai[a][0];
	}

	long long dist(int a, int b) { return depth_euler[a] + depth_euler[b] - 2*depth_euler[lca(a, b)]; }
} LCA;

struct Centroid2
{
	int sz[maxn]; bool mark[maxn];
	long long depth[maxn];
	void dfs(int u, int p) {
		sz[u] = 1;
		for(auto [v, w] : virtual_g[u]) {
			if(mark[v] || v == p) continue;
			dfs(v, u); sz[u] += sz[v];
		}
	}
	int get(int u) {
		for(auto [v, w] : virtual_g[u]) if(!mark[v] && (sz[v]<<1) > sz[u])
			return (sz[u]-=sz[v], sz[v]+=sz[u], get(v));
		return u;
	}
	void calc(int u, int p, vector<int>& vis) {
		vis.push_back(u);
		for(auto [v, w] : virtual_g[u]) if(!mark[v] && v != p)
			depth[v] = depth[u] + w, calc(v, u, vis);
	}
	void decompose(int u) {
		dfs(u, 0);
		u = get(u); mark[u] = 1;

		static vector<int> vis; vis.clear();
		depth[u] = 0; calc(u, 0, vis);

		long long mn = inf;
		for(int x : vis)
			ans[x] = min(ans[x], mn + depth[x] + cost[x]), mn = min(mn, depth[x] + cost[x]);

		mn = inf;
		reverse(all(vis));
		for(int x : vis)
			ans[x] = min(ans[x], mn + depth[x] + cost[x]), mn = min(mn, depth[x] + cost[x]);

		for(auto [v, w] : virtual_g[u]) if(!mark[v])
			decompose(v);
	}
} centroid2;

vector<pii> g[maxn];

struct Centroid
{
	int sz[maxn]; bool mark[maxn];
	long long depth[maxn];
	void dfs(int u, int p) {
		sz[u] = 1;
		for(auto [v, w] : g[u]) {
			if(mark[v] || v == p) continue;
			dfs(v, u); sz[u] += sz[v];
		}
	}
	int get(int u) {
		for(auto [v, w] : g[u]) if(!mark[v] && (sz[v]<<1) > sz[u])
			return (sz[u]-=sz[v], sz[v]+=sz[u], get(v));
		return u;
	}
	void calc(int u, int p, vector<int>& vis) {
		vis.push_back(u);
		for(auto [v, w] : g[u]) if(!mark[v] && v != p)
			depth[v] = depth[u] + w, calc(v, u, vis);
	}
	void decompose(int u) {
		dfs(u, 0);
		u = get(u); mark[u] = 1;
		static vector<int> vis; vis.clear();
		depth[u] = 0; calc(u, 0, vis);
		
		sort(all(vis), [](int x, int y) { return in[x] < in[y]; });

		int tam = sz(vis);
		for(int i = 1; i < tam; i++)
			vis.push_back(LCA.lca(vis[i], vis[i-1]));

		sort(all(vis), [](int x, int y) { return in[x] < in[y]; });
		vis.resize(unique(all(vis)) - vis.begin());

		tam = sz(vis);

		for(int x : vis)
			cost[x] = depth[x] == 0 ? inf : depth[x];
		cost[u] = 0;

		for(int i = 1; i < tam; i++) {
			int lca = LCA.lca(vis[i], vis[i-1]);

			virtual_g[vis[i]].push_back({lca, depth_euler[vis[i]] - depth_euler[lca]});
			virtual_g[lca].push_back({vis[i], depth_euler[vis[i]] - depth_euler[lca]});
		}

		centroid2.decompose(u);

		for(int x : vis)
			virtual_g[x].clear(), cost[x] = inf, centroid2.mark[x] = 0, depth[x] = inf;

		for(auto [v, w] : g[u]) if(!mark[v])
			decompose(v);
	}
} centroid;

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g[a].push_back(pii(b, w));
		g[b].push_back(pii(a, w));
	}
	for(int i = 1; i < n; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		g2[a].push_back(pii(b, w));
		g2[b].push_back(pii(a, w));
	}

	LCA.euler(1);

	memset(ans, 0x3f, sizeof ans);

	centroid.decompose(1);

	for(int i = 1; i <= n; i++)
		printf("%lld%c", ans[i], " \n"[i==n]);
}