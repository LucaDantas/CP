#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e7, maxn = 4194304 + 100;

int lambda, qtd, val, n, t;

struct SegmentTree
{
	pair<int,int> tree[maxn];
	int lazy[maxn];
	void clear() {
		for(int i = 0; i < maxn; i++)
			tree[i] = {inf, inf}, lazy[i] = inf;
		set(1, 0, n, 0, {0, 0});
	}
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j) lazy[node<<1] += lazy[node], lazy[node<<1|1] += lazy[node];
		tree[node].first += lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r, int v) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(lazy[node] = v, flush(node, i, j));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, v);
		upd(node<<1|1, m+1, j, l, r, v);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	void set(int node, int i, int j, int pos, const pair<int,int>& v) {
		flush(node, i, j);
		if(i == j) return (void)(tree[node] = v);
		int m = (i+j) >> 1;
		if(pos <= m) set(node<<1, i, m, pos, v);
		else set(node<<1|1, m+1, j, pos, v);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	pair<int,int> query() { flush(1, 0, n); return tree[1]; }
} seg;
// [0..n]

int a[maxn];

set<int> ativos;
set<pair<int,int>> ordenados;

void get() {
	ativos.clear();
	ordenados.clear();
	seg.clear();
	for(int i = 1; i <= n; i++) {
		pair<int,int> bom = seg.query();
		bom.first += lambda, bom.second++;
		seg.set(1, 0, n, i, bom);
		if(a[i] <= t) {
			ativos.insert(i);
			ordenados.insert({i + t - a[i], i});
		}
		if(ativos.size())
			seg.upd(1, 0, n, 0, *ativos.rbegin(), 1);
		while(ordenados.size() && ordenados.begin()->first == i) {
			ativos.erase(ordenados.begin()->second);
			ordenados.erase(ordenados.begin());
		}
	}
	val = seg.query().first;
	qtd = seg.query().second;
}

int main() {
	int d; scanf("%d %d %d", &n, &d, &t);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int l = 0, r = n, ans = -1;
	while(l <= r) {
		lambda = (l+r) >> 1;
		get();
		if(qtd <= d)
			ans = lambda, r = lambda - 1;
		else l = lambda + 1;
	}
	lambda = ans;
	get();
	printf("%d\n", val - d * ans);
}