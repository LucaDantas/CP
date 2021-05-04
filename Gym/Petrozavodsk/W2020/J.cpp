#include<cstdio>
#include<array>
#include<vector>
#include<algorithm>
using namespace std;

#define pb push_back

constexpr int maxn = 1e6+10;

struct DSU
{
	int pai[maxn], peso[maxn];
	void init() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
} dsu;

vector<int> camada[maxn][2];

vector<int> link[maxn][2];

array<int, 4> coord[maxn];

bool eq(array<int, 4> a, array<int, 4> b) {
	for(int x : {0, 1, 2})
		if(a[x] != b[x])
			return 0;
	return 1;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		dsu.init();

		for(int i = 0; i < maxn; i++)
			link[i][0].clear(), link[i][1].clear(),
			camada[i][0].clear(), camada[i][1].clear(),
			coord[i][0] = coord[i][1] = coord[i][2] = coord[i][3] = 0;

		for(int i = 1; i <= n; i++) {
			for(int x : {0, 1, 2})
				scanf("%d", &coord[i][x]);
			int tipo = coord[i][1]==-1;
			if(coord[i][2] == -1)
				for(int x : {0, 1})
					link[coord[i][!x]][x].pb(i);
			else camada[coord[i][2]][tipo].pb(i);
			coord[i][3] = i;
		}

		for(int i = 1; i < maxn; i++) {
			if(max(camada[i][0].size(), camada[i-1][0].size())
				&& max(camada[i][1].size(), camada[i-1][1].size())) {
				int pai = camada[i][0].size()?camada[i][0][0]:camada[i-1][0][0];
				for(int k : {0, 1})
					for(int j : {i, i-1})
						for(int x : camada[j][k])
							dsu.join(pai, x);
			}
			for(int k : {0, 1}) {
				for(int val : camada[i][k]) {
					int y = coord[val][!k];
					for(int v : {-1, 0, 1}) {
						for(int x : link[y+v][k])
							dsu.join(x, val);
						while(link[y+v][k].size() > 1)
							link[y+v][k].pop_back();
					}
				}
			}
		}

		sort(coord+1, coord+1+n);
		
		for(int i = 1; i <= n; i++) {
			array<int, 4> p = coord[i];
			p[3] = 0;
			for(int x : {0, 1, 2}) {
				++p[x];
				int pai = (int)(lower_bound(coord+1, coord+1+n, p) - coord);
				if(pai <= n && eq(coord[pai], p))
					dsu.join(coord[i][3], coord[pai][3]);
				--p[x];
			}
		}

		int q; scanf("%d", &q);
		while(q--) {
			array<int, 4> p1, p2;
			for(int x : {0, 1, 2})
				scanf("%d", &p1[x]);
			for(int x : {0, 1, 2})
				scanf("%d", &p2[x]);
			p1[3] = 0;
			p2[3] = 0;
			int v1 = -1, v2 = 0;
			for(int x : {0, 1, 2}) {
				int sv = p1[x];
				p1[x] = -1;
				int pai = (int)(lower_bound(coord+1, coord+1+n, p1) - coord);
				if(pai <= n && eq(coord[pai], p1)) v1 = dsu.find(coord[pai][3]);
				p1[x] = sv;

				sv = p2[x];
				p2[x] = -1;
				pai = (int)(lower_bound(coord+1, coord+1+n, p2) - coord);
				
				if(pai <= n && eq(coord[pai], p2)) v2 = dsu.find(coord[pai][3]);
				p2[x] = sv;
			}
			puts(v1==v2?"YES":"NO");
		}
	}
}