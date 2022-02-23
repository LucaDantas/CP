#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, inf = 0x3f3f3f3f;

struct PersistentSegmentTree {
	struct Node {
		Node *l, *r;
		int val;
		Node() : l(this), r(this), val(0) {}
	};
	int t = 0;
	Node *root[maxn]; // we have a root for each version of the seg
	
	PersistentSegmentTree() { root[0] = new Node(); }

	void upd(int pos) {
		++t;
		root[t] = upd(root[t-1], 1, inf, pos);
	}

	Node* upd(Node *node, int i, int j, int pos) { // add v to interval l, r
		Node *aq = new Node();
		*aq = *node;
		
		aq->val++;

		if(i == j) return aq;

		int m = (i+j) >> 1;
		if(pos <= m)
			aq->l = upd(aq->l, i, m, pos);
		else
			aq->r = upd(aq->r, m+1, j, pos);

		return aq;
	}

	int query(Node *node, int i, int j, int l, int r) { // query the interval [l, r] on this version of the seg
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return node->val;
		int m = (i+j) >> 1;
		return query(node->l, i, m, l, r) + query(node->r, m+1, j, l, r);
	}
} segTime;

struct SegmentTree {
	int tree[4*maxn], a[maxn]; // we have a root for each version of the seg

	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(node<<1, i, m);
		build(node<<1|1, m+1, j);
		tree[node] = max(tree[node<<1], tree[node<<1|1]);
	}

	int query(int node, int i, int j, int l, int r) { // query the interval [l, r]
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return max(query(node<<1, i, m, l, r), query(node<<1|1, m+1, j, l, r));
	}
} segX;

int A[maxn], B[maxn];
pair<int,int> X[maxn];

int main() {
	int n, k; scanf("%d %d", &n, &k);
	
	for(int i = 1; i <= n; i++)
		scanf("%d %d", A+i, B+i);

	for(int i = 1; i <= k; i++) {
		int x; scanf("%d", &x); X[i] = {x, i};
		segTime.upd(x);
	}

	sort(X+1, X+k+1);
	for(int i = 1; i <= k; i++)
		segX.a[i] = X[i].second;
	segX.build(1, 1, k);

	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		int a = A[i], b = B[i];
		if(a > b) swap(a, b);
		// quero achar o evento com o maior tempo tal que o valor dele está contido em [a, b[
		int last = 0;
		if(a != b) {
			int itL = (lower_bound(X+1, X+1+k, pair<int,int>(a, 0)) - X);
			int itR = (lower_bound(X+1, X+1+k, pair<int,int>(b, 0)) - X) - 1;

			last = segX.query(1, 1, k, itL, itR);
		}

		if(last != 0)
			ans += (segTime.query(segTime.root[segTime.t], 1, inf, b, inf) -
					segTime.query(segTime.root[last], 1, inf, b, inf)) % 2 == 0 ? b : a;
		else
			ans += segTime.query(segTime.root[segTime.t], 1, inf, b, inf) % 2 == 0 ? A[i] : B[i];
	}

	printf("%lld\n", ans);
}
