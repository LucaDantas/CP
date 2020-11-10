#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define x first
#define y second

constexpr int maxn = 2e3+10;

inline ll sq(int x) { return 1ll*x*x; }
ll dist(pii a, pii b) { return sq(a.x-b.x) + sq(a.y-b.y); }

pii pts[maxn];

struct Edge
{
	int a, b; ll dist;
} edges[maxn*maxn];

struct DSU
{
	int pai[maxn], peso[maxn];
	bool bip, cor[maxn];
	set<int> st;
	DSU() {
		bip = 1;
		for(int i = 0; i < maxn; i++)
			pai[i] = i, peso[i] = 1;
	}
	int find(int x, int& c) {
		while(pai[x] != x)
			c ^= cor[x], x = pai[x];
		return x;
	}
	void join(int a, int b) {
		int c1 = 0, c2 = 0;
		a = find(a, c1), b = find(b, c2);
		st.insert(a), st.insert(b);
		if(a == b)
			return (void)(bip &= c1!=c2);
		if(peso[a] < peso[b])
			swap(a, b), swap(c1, c2);
		cor[b] = 1^c1^c2;
		pai[b] = a;
		peso[b] += peso[a];
	}
	void clear() {
		bip = 1;
		for(int it : st) {
			pai[it] = it; peso[it] = 1;
			cor[it] = 0;
		}
		st.clear();
	}
} dsu;

struct DSU2
{
	int pai[maxn], peso[maxn];
	DSU2() {
		for(int i = 0; i < maxn; i++)
			pai[i] = i, peso[i] = 1;
	}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(peso[a] < peso[b])
			swap(a, b);
		if(a != b)
			pai[b] = a, peso[a] += peso[b];
	}
} dsu2;

int main() {
	int n, cnt = 0; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &pts[i].x, &pts[i].y);
		for(int j = 1; j < i; j++, cnt++)
			edges[cnt] = {j, i, dist(pts[i], pts[j])};
	}
	sort(edges, edges+cnt, [](Edge a, Edge b){return a.dist < b.dist;});
	for(int rep = 0; rep < 2; rep++) {
		for(int i = 0, j = 0; i < cnt; i = j) {
			for(j = i; j < cnt && edges[j].dist == edges[i].dist; j++) {
				dsu.join(edges[j].a, edges[j].b);
				if(dsu2.find(edges[j].a) == dsu2.find(edges[j].b) || dsu2.find(edges[j].a+n) == dsu2.find(edges[j].b+n))
					dsu.bip = 0;
			}
			if(rep) {
				// If we don't absolutely need that group of edges
				// to be grouped we assume that they are not
				// going to be grouped, so we group a -> !b, !a -> b
				// If they need to be grouped we unite a -> b, !a -> !b
				// This is kinda 2-sat style but we don't need to actually
				// code the 2-sat SCC thing because true/false (in this case A, B)
				// Are completely equivalent, and if we have a valid grouping with
				// some subset S belonging to A and its complement belonging to B
				// we can get the same subset belonging to B and its complement
				// inside A, which means we can simply assume that 1 is in A
				// and get who is connected to it
				for(int k = i; k < j; k++)
					if(dsu.bip)
						dsu2.join(edges[k].a, edges[k].b+n),
						dsu2.join(edges[k].a+n, edges[k].b);
					else
						dsu2.join(edges[k].a, edges[k].b),
						dsu2.join(edges[k].a+n, edges[k].b+n);
			}
			else {
				map<int,array<int,2>> mp;
				for(int it : dsu.st) {
					int c = 0; int pai = dsu.find(it, c);
					if(!dsu.bip) c = 0;
					if(!mp[pai][c])
						mp[pai][c] = it;
					else dsu2.join(mp[pai][c], it), dsu2.join(mp[pai][c]+n, it+n);
				}
			}
			dsu.clear();
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans += (dsu2.find(1) == dsu2.find(i));
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++)
		if(dsu2.find(1) == dsu2.find(i))
			printf("%d ", i);
	printf("\n");
}