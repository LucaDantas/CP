#include "train.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())

constexpr int maxn = 5010;

int a[maxn], ligado[maxn], comp[maxn], brabo[maxn], grau[maxn], atv[maxn], cor[maxn];
int n, m, t;

bool mark[maxn];

vector<int> g[maxn], g_rev[maxn], meus[maxn], g_comp[maxn], g_rev_comp[maxn], ord;

void dfs(int u) {
	mark[u] = 1;
	for(int v : g[u])
		if(a[v] && !mark[v]) dfs(v);
	ord.pb(u);
}

void go(int u, int& ok) {
	ok |= ligado[u]<<1;
	comp[u] = t;
	meus[t].pb(u);
	for(int v : g_rev[u]) {
		if(!comp[v] && a[v]) go(v, ok);
		else if(comp[v] == comp[u] && a[v]) ok |= 1;
	}
}

void limpar(int u) {
	brabo[u] = 1, mark[u] = 1;
	for(int v : g_rev_comp[u])
		if(!mark[v] && !cor[v]) limpar(v);
}

vector<int> who_wins(vector<int> A, vector<int> R, vector<int> U, vector<int> V) {
	n = (int)(A.size()), m = (int)(U.size());
	
	for(int i = 0; i < n; i++)
		a[i] = A[i], ligado[i] = R[i];
	
	for(int i = 0; i < m; i++)
		g[U[i]].pb(V[i]), g_rev[V[i]].pb(U[i]);
	
	for(int i = 0; i < n; i++)
		if(a[i] && !mark[i]) dfs(i);
	
	reverse(all(ord));
	for(int i = 0; i < sz(ord); i++) {
		if(comp[ord[i]]) continue;
		int ok = 0; ++t;
		go(ord[i], ok);
		if(ok == 3) brabo[t] = 1;
		if(ok&2) atv[t] = 1;
	}

	for(int i = 0; i < n; i++)
		if(!a[i]) comp[i] = ++t, cor[t] = 1, atv[t] = R[i], meus[t] = {i};

	memset(mark, 0, sizeof mark);
	for(int i = 1; i <= t; i++) {
		for(int u : meus[i])
			for(int v : g[u])
				if(!mark[comp[v]])
					mark[comp[v]] = 1, g_comp[i].pb(comp[v]), g_rev_comp[comp[v]].pb(i);
		for(int x : g_comp[i])
			mark[x] = 0;
	}

	memset(mark, 0, sizeof mark);
	for(int i = 1; i <= t; i++)
		if(brabo[i] && !mark[i]) limpar(i);

	for(int rep = 0; rep < n; rep++) {
		vector<int> fontes;

		memset(mark, 0, sizeof mark);
		for(int i = 1; i <= t; i++)
			if(atv[i]) mark[i] = 1, fontes.pb(i);

		for(int i = 1; i <= t; i++)
			grau[i] = sz(g_comp[i]);
		
		while(fontes.size()) {
			int u = fontes.back(); fontes.pop_back();
			for(int v : g_rev_comp[u]) {
				if(mark[v]) continue;
				--grau[v];
				if(!grau[v] || !cor[v]) fontes.pb(v), mark[v] = 1;
			}
		}

		for(int i = 1; i <= t; i++) {
			grau[i] = sz(g_comp[i]);
			if(!mark[i] && !brabo[i]) fontes.pb(i);
		}

		memset(mark, 0, sizeof mark);

		for(int x : fontes)
			mark[x] = 1;

		while(fontes.size()) {
			int u = fontes.back(); fontes.pop_back();
			for(int v : g_rev_comp[u]) {
				if(mark[v]) continue;
				--grau[v];
				if((!grau[v] && !brabo[v]) || cor[v]) fontes.pb(v), mark[v] = 1;
			}
		}

		for(int i = 1; i <= t; i++)
			atv[i] &= !mark[i];
	}

	vector<int> ans(n);

	for(int i = 0; i < n; i++)
		ans[i] = !mark[comp[i]];

	return ans;	
}
