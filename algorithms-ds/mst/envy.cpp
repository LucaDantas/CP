#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())
#define ff first
#define ss second

constexpr int maxn = 5e5+10;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}

	struct Rollback
	{
		int a, b, peso_a;
	};

	vector<Rollback> state;

	int find(int x) {
		if(pai[x] == x) return x;
		return find(pai[x]);
	}

	bool join(int a, int b) {
		a = find(a); b = find(b);
		if(a == b)
			return false;
		if(peso[a] < peso[b])
			swap(a, b);
		state.pb({a, b, peso[a]});
		pai[b] = a;
		peso[a] += peso[b];
		return true;
	}

	void rollback() {
		Rollback opa = state.back();
		state.pop_back();
		pai[opa.b] = opa.b;
		peso[opa.a] = opa.peso_a;
	}	
} dsu;

struct Edge
{
	int a, b, w;
} edges[maxn];

int ok[maxn];

vector<int> edge_p[maxn];

vector<pair<int,vector<int>>> opa[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, w; scanf("%d %d %d", &a, &b, &w);
		edges[i] = {a, b, w};
		edge_p[w].pb(i);
	}
	
	int q; scanf("%d", &q);
	for(int pos = 0; pos < q; pos++) {
		ok[pos] = 1;
		int tam; scanf("%d", &tam);
		vector<int> here(tam);
		for(int j = 0; j < tam; j++)
			scanf("%d", &here[j]), here[j]--;
		sort(all(here), [&](int a, int b){
			return edges[a].w < edges[b].w;
		});
		vector<int> add;
		add.pb(here[0]);
		for(int i = 1; i < sz(here); i++) {
			if(edges[here[i]].w == edges[here[i-1]].w)
				add.pb(here[i]);
			else {
				opa[edges[here[i-1]].w].pb({pos, add});
				add.clear();
				add.pb(here[i]);
			}
		}
		if(sz(add))
			opa[edges[here.back()].w].pb({pos, add});
	}

	for(int peso = 1; peso < maxn; peso++) {
		for(auto query : opa[peso]) {
			int id = query.ff, qtd = 0;
			for(auto e : query.ss)
				if(!dsu.join(edges[e].a, edges[e].b))
					ok[id] = 0;
				else qtd++;
			while(qtd--)
				dsu.rollback();
		}
		for(auto e : edge_p[peso])
			dsu.join(edges[e].a, edges[e].b);
	}

	for(int i = 0; i < q; i++)
		puts(ok[i]?"YES":"NO");
}