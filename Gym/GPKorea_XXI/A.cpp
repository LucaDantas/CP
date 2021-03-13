#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 25e4+10;

struct SegmentTree
{
	long long tree[4*maxn], a[maxn];
	int lazy[4*maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(node<<1, i, m);
		build(node<<1|1, m+1, j);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		tree[node] += lazy[node];
		if(i == j) return (void)(lazy[node] = 0);
		lazy[node<<1] += lazy[node];
		lazy[node<<1|1] += lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r, int v) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) {
			lazy[node] = v;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, v);
		upd(node<<1|1, m+1, j, l, r, v);
		tree[node] = min(tree[node<<1], tree[node<<1|1]);
	}
	bool query() { return tree[1] >= 0ll; }
} seg;

int a[maxn], b[maxn], sorted_a[maxn];
long long s[maxn], pref[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sorted_a[i] = a[i];
	sort(sorted_a+1, sorted_a+n+1, [](int x, int y) { return x > y; });
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]), ++s[min(n, b[i])];
	for(int i = n; i > 0; i--)
		s[i] += s[i+1];
	for(int i = 1; i <= n; i++) {
		s[i] += (i>1?s[i-1]:0);
		pref[i] = sorted_a[i] + (i?pref[i-1]:0);
		seg.a[i] = s[i] - pref[i];
	}
	memset(seg.tree, 0x3f, sizeof seg.tree);
	seg.build(1, 1, n);
	int q; scanf("%d", &q);
	while(q--) {
		int t, i; scanf("%d %d", &t, &i);
		if(t == 1) {
			int p = (int)(lower_bound(sorted_a+1, sorted_a+n+1, a[i],
				[](int x, int y) { return x > y; }) - sorted_a);
			++sorted_a[p], ++a[i]; seg.upd(1, 1, n, p, n, -1);
		}
		if(t == 2) {
			int p = (int)(upper_bound(sorted_a+1, sorted_a+n+1, a[i],
				[](int x, int y) { return x > y; }) - sorted_a - 1);
			--sorted_a[p], --a[i]; seg.upd(1, 1, n, p, n, 1);
		}
		if(t == 3)
			if(++b[i] <= n) seg.upd(1, 1, n, b[i], n, 1);
		if(t == 4)
			if(b[i] <= n) seg.upd(1, 1, n, b[i]--, n, -1);
		puts(seg.query()?"1":"0");
	}
}