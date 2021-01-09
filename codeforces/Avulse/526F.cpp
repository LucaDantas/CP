#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define ff first
#define ss second
#define all(a) (a).begin(),(a).end()

constexpr int maxn = 3e5+10, inf = 0x3f3f3f3f;

struct SegmentTree
{
	pii tree[4*maxn];
	int lazy[4*maxn];
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = {inf, 1});
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = {inf, tree[2*node].ss+tree[2*node+1].ss};
	}
	void flush(int node, int i, int j) {
		if(!lazy[node]) return;
		if(i != j) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		tree[node].ff += lazy[node];
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r, int v) {
		flush(node, i, j);
		if(i > r || j < l) return;
		if(i >= l && j <= r) {
			lazy[node] += v;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r, v); upd(2*node+1, m+1, j, l, r, v);
		if(tree[2*node].ff == tree[2*node+1].ff)
			tree[node] = {tree[2*node].ff,
				tree[2*node].ss + tree[2*node+1].ss};
		else tree[node] = min(tree[2*node], tree[2*node+1]);
	}
	pii query(int n) {
		flush(1, 0, n-1);
		return tree[1];
	}
} seg;

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n);
	vector<pii> b(n);
	for(pii& x : b)
		scanf("%d %d", &x.ff, &x.ss);
	sort(all(b), [](pii x, pii y){return x.ff < y.ff;});
	for(int i = 0; i < n; i++)
		a[i] = b[i].ss;
	seg.build(1, 0, n-1);
	stack<int> maior, menor;
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		seg.upd(1, 0, n-1, i, i, -inf + 1);

		int pos = i;
		while(maior.size() && a[i] > a[maior.top()]) {
			seg.upd(1, 0, n-1, maior.top()+1, pos, a[i] - a[pos]);
			pos = maior.top();
			maior.pop();
		}
		int esq = maior.size()?maior.top()+1:0;
		seg.upd(1, 0, n-1, esq, pos, a[i] - a[pos]);
		
		pos = i;
		while(menor.size() && a[i] < a[menor.top()]) {
			seg.upd(1, 0, n-1, menor.top()+1, pos, - a[i] + a[pos]);
			pos = menor.top();
			menor.pop();
		}
		esq = menor.size()?menor.top()+1:0;
		seg.upd(1, 0, n-1, esq, pos, - a[i] + a[pos]);

		seg.upd(1, 0, n-1, 0, i, -1);

		maior.push(i);
		menor.push(i);
		if(!seg.query(n).ff)
			ans += seg.query(n).ss;
	}
	printf("%lld\n", ans);
}