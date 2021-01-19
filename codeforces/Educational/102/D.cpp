#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

char s[maxn];

struct Node {
	int mx, mn, tot;
};

Node combine(Node a, Node b) {
	return {max(a.mx, a.tot+b.mx), min(a.mn, a.tot+b.mn), a.tot+b.tot};
}

struct SegmentTree
{
	Node tree[4*maxn];
	void build(int node, int l, int r) {
		if(l == r) {
			if(s[l] == '+') tree[node] = {1, 0, 1};
			else tree[node] = {0, -1, -1};
			return;
		}
		int m = (l+r) >> 1;
		build(2*node, l, m); build(2*node+1, m+1, r);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	Node query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return {0, 0, 0};
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return combine(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}
} seg;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		scanf(" %s", s);
		seg.build(1, 0, n-1);
		while(m--) {
			int l, r; scanf("%d %d", &l, &r);
			--l, --r;
			Node ans = {0, 0, 0};
			if(l == 0 && r == n-1);
			else if(l == 0) ans = seg.query(1, 0, n-1, r+1, n-1);
			else if(r == n-1) ans = seg.query(1, 0, n-1, 0, l-1);
			else ans = combine(seg.query(1, 0, n-1, 0, l-1),
				seg.query(1, 0, n-1, r+1, n-1));
			printf("%d\n", ans.mx - ans.mn + 1);
		}
	}
}