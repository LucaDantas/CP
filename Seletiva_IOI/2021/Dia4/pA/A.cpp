#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back
#define all(a) (a.begin(), a.end())
#define sz(a) (int)(a.size())

constexpr int maxn = 2e5+10;

int n, L, R, x;

vector<int> g[maxn];

void dfs(int u, int p = 0) {
	if(sz(g[u]) == 1) ++x;
	for(int v : g[u])
		if(v != p) dfs(v, u);
}

int main() {
	scanf("%d %d %d", &n, &L, &R);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	dfs(1);
	printf("%lld\n", 1ll * x * (x-1) / 2);
}