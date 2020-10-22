#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10;

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
	int a, b, w, ok;
} edges[maxn];

vector<pii> g[maxn];

int d[maxn];

void dfs(int u, int p) {
	for(pii pp : g[u]) {
		int v = pp.ff, w = pp.ss;
		if(v != p) {
			d[v] = d[u]^w;
			dfs(v, u);
		}
	}
}

// Version 1 (agnaldo way to code)

vector<int> base;

int check(int x) {
	for(int y : base)
		x = min(x, x^y);
	return x;
}

/*

// VERSION 2 (Leo / Lucio way to code)

int base[30];

void check(int x) {
	for(int l = 29; l >= 0; l--) {
		if(!(x&(1 << l))) continue;
		if(!base[l]) { base[l] = x; break; }
		x ^= base[l];
	}
}

int get(int x) {
	for(int l = 29; l >= 0; l--) {
		if(!(x&(1 << l))) continue;
		x ^= base[l];
	}
	return x;
}

*/

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		if(dsu.join(a, b)) {
			edges[i] = {a, b, w, 1};
			g[a].pb({b, w});
			g[b].pb({a, w});
		} else edges[i] = {a, b, w, 0};
	}
	dfs(1, 0);
	for(int i = 0; i < m; i++) {
		if(edges[i].ok) continue;
		int a = edges[i].a, b = edges[i].b, w = edges[i].w;
		int x = check(d[a]^w^d[b]);
		if(x) base.pb(x);
	}
	printf("%d\n", check(d[1]^d[n]));
	// printf("%d\n", get(d[1]^d[n])); // (V2)
}