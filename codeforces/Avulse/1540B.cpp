#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 200 + 10;
constexpr int mod = 1000000007;

int fat[maxn], inv[maxn], inv_fat[maxn], f[maxn][maxn];

void calc() {
	inv[1] = fat[1] = fat[0] = inv_fat[0] = inv_fat[1] = 1;
	for(int i = 2; i < maxn; i++) {
		inv[i] = (int)(mod - (1ll * (mod/i) * inv[mod%i] % mod));
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}
	for(int i = 1; i < maxn; i++)
		f[0][i] = 1;
	for(int i = 1; i < maxn; i++)
		for(int j = 1; j < maxn; j++)
			f[i][j] = (int)(1ll * (f[i-1][j] + f[i][j-1]) * ((mod+1) / 2) % mod);
}

int choose(int a, int b) { return (int)((1ll * fat[a] * inv_fat[b] % mod) * inv_fat[a-b] % mod); }

int pb(int a, int b) { return f[a][b]; }

void add(int& a, long long b) { a += (int)b; if(a >= mod) a -= mod; }

vector<int> g[maxn], opa[maxn];

int ans = 0, depth[maxn];

bool mark[maxn][maxn];

void dfs_par(int a, int b, int da, int db) {
	if(a < b) swap(a, b), swap(da, db);
	if(mark[a][b]) return;
	mark[a][b] = 1;
	add(ans, pb(da, db));
	for(int v : g[a]) if(depth[v] > depth[a])
		dfs_par(v, b, da+1, db);
	for(int v : g[b]) if(depth[v] > depth[b])
		dfs_par(a, v, da, db+1);
}

void dfs(int u, int p) {
	depth[u] = depth[p] + 1;
	opa[u].clear();
	for(int v : g[u]) if(v != p) {
		dfs(v, u);
		for(int x : opa[v]) opa[u].pb(x);
	}
	for(int v : g[u]) for(int w : g[u]) if(v != w && v != p && w != p)
		dfs_par(v, w, 1, 1);
	for(int x : opa[u])
		if(u > x) ++ans;
	opa[u].pb(u);
}

int main() {
	calc();
	int n; scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	for(int i = 1; i <= n; i++) {
		dfs(i, 0);
		memset(mark, 0, sizeof mark);
	}
	ans = (int)(1ll * ans * inv[n] % mod);
	printf("%d\n", ans);
}
