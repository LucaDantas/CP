#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,ll>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 2e5+10;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b)
			return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return 1;
	}
} dsu;

struct Edge
{
	int a, b;
	ll w;
	bool ok;
} edges[maxn];

vector<pii> g[maxn];

ll d[maxn];

void dfs(int u, int p) {
	for(pii pp : g[u]) {
		int v = pp.ff;
		ll w = pp.ss;
		if(v != p) {
			d[v] = d[u]^w;
			dfs(v, u);
		}
	}
}

vector<ll> base;

ll check(ll x) {
	for(ll y : base)
		x = min(x, x^y);
	return x;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b;
		ll w; scanf("%d %d %lld", &a, &b, &w);
		if(dsu.join(a, b)) {
			edges[i] = {a, b, w, 1};
			g[a].pb({b, w});
			g[b].pb({a, w});
		} else edges[i] = {a, b, w, 0};
	}
	dfs(1, 0);
	for(int i = 0; i < m; i++) {
		if(edges[i].ok) continue;
		int a = edges[i].a, b = edges[i].b;
		ll w = edges[i].w;
		ll x = check(d[a]^w^d[b]);
		if(x) base.pb(x);
	}
	ll ans = 0;
	for(ll x : base)
		ans = max(ans, ans^x);
	printf("%lld\n", ans);
}