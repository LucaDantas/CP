#include<bits/stdc++.h>
using namespace std;
 
using pii = pair<int,int>;
 
#define ff first
#define ss second
#define pb push_back
#define all(a) (a).begin(), (a).end()
 
constexpr int maxn = 2e6+10, inf = 0x3f3f3f3f, mod = 1000000007;
 
struct SegmentTree
{
	int base[maxn], tree[4*maxn], k;
	SegmentTree(int _k) : k(_k) {}
	inline int op(int a, int b) {return k?max(a,b):min(a,b);}
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = base[i]?base[i]:(k?-inf:inf));
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = op(tree[2*node], tree[2*node+1]);
	}
	void rm(int node, int i, int j, int pos) {
		if(i == j) return (void)(tree[node] = k?-inf:inf);
		int m = (i+j) >> 1;
		if(pos <= m) rm(2*node, i, m, pos);
		else rm(2*node+1, m+1, j, pos);
		tree[node] = op(tree[2*node], tree[2*node+1]);
	}
	int find(int node, int i, int j, int l, int r, int val) {
		if(i > r || j < l || (k && tree[node] < val) || (!k && tree[node] > val)) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		if(k) {
			int p1 = find(2*node, i, m, l, r, val);
			if(p1 == -1) return find(2*node+1, m+1, j, l, r, val);
			return p1;
		} else {
			int p1 = find(2*node+1, m+1, j, l, r, val);
			if(p1 == -1) return find(2*node, i, m, l, r, val);
			return p1;
		}
	}
} seg0(0), seg1(1);
 
pii a[maxn];
 
int pos[2*maxn], cor[maxn], mark[maxn], n;
 
void dfs(int i, int C) {
	assert(!mark[i]);
	cor[i] = C;
	mark[i] = 1;
	seg0.rm(1, 1, 2*n, a[i].ss);
	seg1.rm(1, 1, 2*n, a[i].ff);
	int next;
	while((next = seg1.find(1, 1, 2*n, a[i].ff+1, a[i].ss, a[i].ss)) != -1)
		dfs(pos[next], !C);
	while((next = seg0.find(1, 1, 2*n, a[i].ff, a[i].ss-1, a[i].ff)) != -1)
		dfs(pos[next], !C);
}
 
int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}
 
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].ff, &a[i].ss);
		pos[a[i].ff] = i, pos[a[i].ss] = i;
		seg1.base[a[i].ff] = a[i].ss, seg0.base[a[i].ss] = a[i].ff;
	}
 
	seg0.build(1, 1, 2*n);
	seg1.build(1, 1, 2*n);
 
	int cc = 0;
	for(int i = 1; i <= n; i++)
		if(!mark[i]) ++cc, dfs(i, 0);
 
	vector<int> b, w, st;
	for(int i = 1; i <= n; i++)
		if(cor[i])
			w.pb(a[i].ff), w.pb(a[i].ss);
	else b.pb(a[i].ff), b.pb(a[i].ss);
	sort(all(w)), sort(all(b));
 
	int ok = 1;
	for(int x : w)
		if(st.size() && st.back() == pos[x])
			st.pop_back();
	else st.pb(pos[x]);
	if(st.size()) ok = 0;
 
	st.clear();
	for(int x : b)
		if(st.size() && st.back() == pos[x])
			st.pop_back();
	else st.pb(pos[x]);
	if(st.size()) ok = 0; 
 
	printf("%d\n", ok?power(2, cc):0);
}