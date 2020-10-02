#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back

constexpr int maxn = 2e5+10;
constexpr int B = 5000;

struct DSU
{
	int pai[maxn], peso[maxn], bip;
	bool par[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; bip = 1; memset(par, 0, sizeof par);}
	
	struct Rollback
	{
		int x, y, par_y, peso_x, bipartido;
	};

	vector<Rollback> state;

	void rollback() {
		assert(state.size());
		Rollback st = state.back();
		state.pop_back();
		pai[st.y] = st.y;
		par[st.y] = st.par_y;
		peso[st.x] = st.peso_x;
		bip = st.bipartido;
	}

	int find(int x, int& par_x)	{
		while(pai[x] != x)
			 par_x ^= par[x], x = pai[x];
		return x;
	}

	void join(int x, int y) {
		int par_x = 0, par_y = 0;
		x = find(x, par_x), y = find(y, par_y);

		if(peso[x] < peso[y])
			swap(x, y);
		
		// We know that we'll link y -> x if we link at all
		state.pb({x, y, par[y], peso[x], bip});
		
		if(x != y) {
			pai[y] = x;
			peso[x] += peso[y];
			par[y] = 1^par_x^par_y;
		} else if(par_x == par_y) bip = 0;
	}
} dsu;

pii edges[maxn];

struct Query
{
	int l, r, block, id;
} Q[maxn];

bool ans[maxn];

int main() {
	int n, m, q; scanf("%d %d %d", &n, &m, &q);
	
	for(int i = 0; i < m; i++)
		scanf("%d %d", &edges[i].first, &edges[i].second);

	for(int i = 0; i < q; i++)
		scanf("%d %d", &Q[i].l, &Q[i].r), Q[i].l--, Q[i].r--, Q[i].block = Q[i].l/B, Q[i].id = i;
	
	sort(Q, Q+q, [](Query a, Query b){
		if(a.block == b.block) return a.r > b.r;
		else return a.block < b.block;
	});

	for(int i = 0, now = 0, ptrL = 0, ptrR = m-1; i < q; i++) {
		if(Q[i].block != now) {
			while(ptrR < m-1)
				dsu.rollback(), ptrR++;
			while(ptrL < Q[i].block*B)
				dsu.join(edges[ptrL].first, edges[ptrL].second), ptrL++;
			now = Q[i].block;
		}
		while(ptrR > Q[i].r)
			dsu.join(edges[ptrR].first, edges[ptrR].second), ptrR--;
		
		int add = 0;		
		while(ptrL < Q[i].l)
			dsu.join(edges[ptrL].first, edges[ptrL].second), ptrL++, add++;

		ans[Q[i].id] = !dsu.bip;

		while(add--)
			dsu.rollback(), ptrL--;
	}

	for(int i = 0; i < q; i++)
		puts(ans[i]?"YES":"NO");
}