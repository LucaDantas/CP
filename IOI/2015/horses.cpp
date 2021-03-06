#include "horses.h"
#include<cmath>
#include<algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

using pdi = pair<double, int>;

#define ff first
#define ss second

constexpr int maxn = 5e5+10, mod = 1000000007;

int *x, *y, n, val_pref[maxn];

double pref[maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

struct SegmentTree
{
	pdi tree[4*maxn], lazy[4*maxn];
	void build(int node, int i, int j) {
		lazy[node] = {0, 1};
		if(i == j) {
			tree[node] = {pref[i] + log2(y[i]), (int)(1ll * val_pref[i] * y[i] % mod)};
			return;
		}
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	void flush(int node, int i, int j) {
		if(!lazy[node].ff) return;
		if(i != j) {
			lazy[2*node].ff += lazy[node].ff;
			lazy[2*node+1].ff += lazy[node].ff;
			lazy[2*node].ss = (int)(1ll * lazy[node].ss * lazy[2*node].ss % mod);
			lazy[2*node+1].ss = (int)(1ll * lazy[node].ss * lazy[2*node+1].ss % mod);
		}
		tree[node].ff += lazy[node].ff;
		tree[node].ss = (int)(1ll * tree[node].ss * lazy[node].ss % mod);
		lazy[node] = {0, 1};
	}
	void upd(int node, int i, int j, int l, int r, pdi val) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) {
			lazy[node] = val;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r, val);
		upd(2*node+1, m+1, j, l, r, val);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	pdi query() {
		flush(1, 0, n-1);
		return tree[1];
	}
} seg;

int init(int N, int X[], int Y[]) {
	x = X; y = Y; n = N;
	for(int i = 0; i < n; i++) {
		pref[i] = (i?pref[i-1]:0) + log2(x[i]);
		val_pref[i] = (int)(1ll * (i?val_pref[i-1]:1) * x[i] % mod);
	}
	seg.build(1, 0, n-1);
	return seg.query().ss;
}

int updateX(int pos, int val) {
	int mudar = (int)(1ll * val * power(x[pos], mod-2) % mod);
	pdi v = {log2(val) - log2(x[pos]), mudar};
	seg.upd(1, 0, n-1, pos, n-1, v);
	x[pos] = val;
	return seg.query().ss;
}

int updateY(int pos, int val) {
	int mudar = (int)(1ll * val * power(y[pos], mod-2) % mod);
	pdi v = {log2(val) - log2(y[pos]), mudar};
	y[pos] = val;
	seg.upd(1, 0, n-1, pos, pos, v);
	return seg.query().ss;
}
