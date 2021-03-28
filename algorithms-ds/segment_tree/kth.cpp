#include <cstdio>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

struct Node
{
	Node *l, *r; int val;
	Node() : l(this), r(this), val(0) {}
} *root[maxn];

struct PersistentSegmentTree
{
	Node* upd(Node *base, int i, int j, int pos, int v) {
		Node* node = new Node();
		*node = *base;

		node->val += v;

		if(i == j) return node;
		
		int m = (i+j) >> 1;
		
		if(pos <= m) node->l = upd(node->l, i, m, pos, v);
		else node->r = upd(node->r, m+1, j, pos, v);

		return node;
	}

	int query(Node* node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return node->val;
		int m = (i+j) >> 1;
		return query(node->l, i, m, l, r) + query(node->r, m+1, j, l, r);
	}

	int find(Node* rmv, Node* add, int i, int j, int k) {
		if(add->val - rmv->val < k) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int v = find(rmv->l, add->l, i, m, k);
		if(v != -1) return v;
		return find(rmv->r, add->r, m+1, j, k - (add->l->val - rmv->l->val));
	}
} seg;

int a[maxn];

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	root[0] = new Node();
	for(int i = 0; i < n; i++)
		root[i+1] = seg.upd(root[i], -inf, inf, a[i], 1);
	while(q--) {
		int l, r, k; scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", seg.find(root[l-1], root[r], -inf, inf, k));
	}
}