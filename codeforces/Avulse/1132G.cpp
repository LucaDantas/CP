#include<bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())
#define pb push_back

constexpr int maxn = 1e6+10;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn];
	void flush(int node, int i, int j) {
		if(!lazy[node])
			return;
		if(i != j) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		tree[node] += lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(j < l || i > r)
			return;
		if(i >= l && j <= r)
			return (void)(lazy[node] = 1, flush(node, i, j));
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r); upd(2*node+1, m+1, j, l, r);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
	int query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(j < l || i > r)
			return 0;
		if(i >= l && j <= r)
			return tree[node];
		int m = (i+j) >> 1;
		return max(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}
} seg;

stack<int> st;

int main() {
	int k, n; scanf("%d %d", &n, &k);
	vector<int> a(n);
	for(int& x : a)
		scanf("%d", &x);
	for(int i = 0; i < k; i++) {
		while(st.size() && a[i] > a[st.top()])
			st.pop();
		int pos = st.size()?st.top()+1:0;
		st.push(i);
		seg.upd(1, 0, n-1, pos, i);
	}
	for(int i = 0; i + k < n; i++) {
		printf("%d ", seg.query(1, 0, n-1, i, i+k));
		while(st.size() && a[i+k] > a[st.top()])
			st.pop();
		int pos = st.size()?max(st.top()+1, i):i;
		st.push(i+k);
		seg.upd(1, 0, n-1, pos, i+k);
	}
	
	printf("%d\n", seg.query(1, 0, n-1, n-k, n-1));
}