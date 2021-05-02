#include <cstdio>
#include <cassert>
#include <vector>

constexpr int maxn = 1e7+10;

int ptr = 0;

struct Node
{
	bool v;
	int l, r;
} tree[maxn];

int novo[maxn], antigo[maxn];

void create() {
	tree[ptr].l = tree[ptr].r = ptr;
	tree[ptr].v = 0;
	++ptr;
}

int set(int base, int l, int r, int pos) {
	int node = ptr; create();
	tree[node] = tree[base];
	tree[node].v = 1;
	if(l == r) return node;
	int m = (l+r) >> 1;
	if(pos <= m) tree[node].l = set(node, l, m, pos);
	else tree[node].r = set(node, m+1, r, pos);
	return node;
}

int merge(int a, int b) {
	if(tree[a].v && tree[b].v) {
		int node = ptr; create();
		tree[node].v = 1;
		tree[node].l = merge(tree[a].l, tree[b].l);
		tree[node].r = merge(tree[a].r, tree[b].r);
		return node;
	}
	if(tree[a].v) return a;
	return b;
}

int query(int node, int l, int r, int pos) {
	if(l == r) return tree[node].v;
	int m = (l+r) >> 1;
	if(pos <= m) return query(tree[node].l, l, m, pos);
	return query(tree[node].r, m+1, r, pos);
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	novo[0] = ptr; create();
	for(int i = 1; i <= n; i++)
		novo[i] = set(novo[0], 1, n, i);
	for(int i = 0; i < n + k - 1; i++) {
		char c; scanf(" %c", &c);
		if(c == 'S') {
			int a, b; scanf("%d %d", &a, &b);
			int node = merge(novo[a], novo[b]);
			novo[a] = node;
			novo[b] = node;
		} else if(c == 'Q') {
			int a, b; scanf("%d %d", &a, &b);
			puts(query(novo[a], 1, n, b) ? "yes" : "no");
		} else {
			assert(0);
		}
	}
}