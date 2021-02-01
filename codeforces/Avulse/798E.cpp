#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

bool mark[maxn];

int a[maxn], b[maxn], n;

vector<int> ans;

struct SegmentTree
{
	int tree[4*maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = b[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	void upd(int node, int i, int j, int p) {
		if(i == j) return (void)(tree[node] = 0);
		int m = (i+j) >> 1;
		if(p <= m) upd(2*node, i, m, p);
		else upd(2*node+1, m+1, j, p);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	int query(int node, int i, int j, int r, int v) {
		if(i > r || tree[node] <= v) return 0;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int p1 = query(2*node, i, m, r, v);
		return p1?p1:query(2*node+1, m+1, j, r, v);
	}
} seg;

void dfs(int u) {
	mark[u] = 1;
	seg.upd(1, 1, n, u);
	if(!mark[b[u]])
		dfs(b[u]);
	int v = seg.query(1, 1, n, a[u]-1, u);
	while(v) {
		dfs(v);
		v = seg.query(1, 1, n, a[u]-1, u);
	}
	ans.push_back(u);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		b[i] = n+1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if(a[i] != -1) b[a[i]] = i;
		else a[i] = n+1;
	}
	seg.build(1, 1, n);
	mark[n+1] = 1;
	for(int i = 1; i <= n; i++)
		if(!mark[i])
			dfs(i);
	vector<int> final(n+1);
	for(int i = 0; i < n; i++)
		final[ans[i]] = i+1;
	for(int i = 1; i <= n; i++)
		printf("%d ", final[i]);
	printf("\n");
}