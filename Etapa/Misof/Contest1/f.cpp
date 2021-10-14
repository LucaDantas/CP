#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

struct SegmentTree
{
	int tree[4*maxn], a[maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(node<<1, i, m); build(node<<1|1, m+1, j);
		tree[node] = max(tree[node<<1], tree[node<<1|1]);
	}
	void upd(int node, int i, int j, int pos) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		if(pos <= m) upd(node<<1, i, m, pos);
		else upd(node<<1|1, m+1, j, pos);
		tree[node] = max(tree[node<<1], tree[node<<1|1]);
	}
	int findL(int node, int i, int j, int val, int lim) {
		if(tree[node] < val || i > lim) return -1;
		if(i == j) return i;

		int m = (i+j) >> 1;
		
		int ans1 = findL(node<<1|1, m+1, j, val, lim);
		if(ans1 != -1) return ans1;
		
		return findL(node<<1, i, m, val, lim);
	}

	int findR(int node, int i, int j, int val, int lim) {
		if(tree[node] < val || j < lim) return -1;
		if(i == j) return i;

		int m = (i+j) >> 1;

		int ans1 = findR(node<<1, i, m, val, lim);
		if(ans1 != -1) return ans1;

		return findR(node<<1|1, m+1, j, val, lim);
	}
} seg;

int main() {
	int n; scanf("%d", &n);
	int q; scanf("%d", &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", &seg.a[i]);
	seg.build(1, 1, n);

	while(q--) {
		char c; scanf(" %c", &c);
		int pos, val; scanf("%d %d", &pos, &val);
		++pos;
		if(c == 'C') {
			int opa1 = seg.findL(1, 1, n, val, pos);
			int opa2 = seg.findR(1, 1, n, val, pos);
			if(opa1 != -1 && opa2 != -1)
				if(opa2 - pos >= pos - opa1) printf("%d\n", pos-opa1);
				else printf("%d\n", opa2-pos);
			else if(opa1 != -1) printf("%d\n", pos-opa1);
			else if(opa2 != -1) printf("%d\n", opa2-pos);
			else puts("Too high!");
		} else {
			seg.a[pos] = val;
			seg.upd(1, 1, n, pos);
		}
	}
}
