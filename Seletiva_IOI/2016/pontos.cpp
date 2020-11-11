#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

int x[maxn], y[maxn], z[maxn];

struct DSU
{
	int pai[maxn], peso[maxn];
	array<int, (1<<3)> bom[maxn];
	void init(int n) {
		for(int i = 0; i < n; i++) {
			pai[i] = i, peso[i] = 1;
			for(int mask = 0; mask < (1 << 3); mask++)
				bom[i][mask] = ((mask&1)>0?1:-1)*x[i] + ((mask&2)>0?1:-1)*y[i] + ((mask&4)>0?1:-1)*z[i];
		}
	}
	struct Roolback
	{
		int a, b, peso_a;
		array<int, (1<<3)> bom_a, bom_b;
	};
	vector<Roolback> st;
	int find(int x) {return pai[x]==x?x:find(pai[x]);}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b)
			return;
		if(peso[a] < peso[b])
			swap(a, b);
		st.pb({a, b, peso[a], bom[a], bom[b]});
		peso[a] += peso[b];
		pai[b] = a;
		for(int mask = 0; mask < (1 << 3); mask++)
			bom[a][mask] = max(bom[a][mask], bom[b][mask]);
	}
	void roolback() {
		assert(st.size());
		int a = st.back().a, b = st.back().b;
		pai[b] = b;
		peso[a] = st.back().peso_a;
		for(int mask = 0; mask < (1 << 3); mask++)
			bom[a][mask] = st.back().bom_a[mask];
		for(int mask = 0; mask < (1 << 3); mask++)
			bom[b][mask] = st.back().bom_b[mask];
		st.pop_back();
	}
} dsu;

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d %d", &x[i], &y[i], &z[i]);
	dsu.init(n);
	int q; scanf("%d", &q);
	while(q--) {
		int t; scanf("%d", &t);
		if(t&1) {
			int i, j; scanf("%d %d", &i, &j); i--, j--;
			if(t == 1)
				dsu.join(i, j);
			else {
				int ans = 0;
				for(int mask = 0; mask < (1 << 3); mask++)
					ans = max(ans, dsu.bom[dsu.find(i)][mask] + dsu.bom[dsu.find(j)][mask^7]);
				printf("%d\n", ans);
			}
		} else dsu.roolback();
	}
}