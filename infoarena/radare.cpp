#include <bits/stdc++.h>

// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")

using namespace std;
using ll = long long;
using vi = vector<int>;

#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define eb emplace_back

constexpr int maxn = 3010;
constexpr int mod = 31333;

int pot[maxn];

void calc() {
	pot[0] = 1;
	rep(i,1,maxn) {pot[i] = pot[i-1]*2; if(pot[i] >= mod) pot[i] -= mod;}
}

int cost[maxn], in[maxn], out[maxn], tempo[maxn], sz[maxn], tt;

vi g[maxn];

void dfs(int u, int p) {
	in[u] = ++tt; tempo[tt] = u; sz[u] = 1;
	for(auto v : g[u])
		if(v != p) dfs(v, u), sz[u] += sz[v];
	out[u] = tt;
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

int main() {
	calc();
	// freopen("radare.in", "r", stdin);
	// freopen("radare.out", "w", stdout);
	int n, p; scanf("%d %d", &n, &p);
	
	rep(i,1,n) {
		int u, v; scanf("%d %d", &u, &v);
		g[u].eb(v);
		g[v].eb(u);
	}

	rep(i,1,n+1) scanf("%d", &cost[i]);

	dfs(1, -1);

	vector<vi> dp(n+2, vi(p+1));

	dp[n+1][0] = 1; // fake state just for everyone to look and have a base case

	for(int i = n; i > 1; i--) {
		int u = tempo[i];
		for(int j = 0; j <= p; j++) {
			dp[i][j] = pot[sz[u]-1] * dp[out[u]+1][j] % mod;
			if(j >= cost[u])
				add_self(dp[i][j], dp[i+1][j-cost[u]]);
		}
	}

	printf("%d\n", dp[2][p - cost[1]]);
}
