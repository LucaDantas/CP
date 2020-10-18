#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10;

set<pii> st;

struct Seg
{
	ll tree[4*maxn], lazy[4*maxn];
	void flush(int node, int l, int r) {
		if(!lazy[node])
			return;
		if(l != r) {
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		tree[node] += lazy[node] * (r - l + 1);
		lazy[node] = 0;
	}
	void upd(int node, int i, int j, int l, int r, int x) {
		flush(node, i, j);
		if(i > r || j < l)
			return;
		if(i >= l && j <= r) {
			lazy[node] = x;
			flush(node, i, j);
			return;
		}
		int m = (i+j) >> 1;
		upd(2*node, i, m, l, r, x); upd(2*node+1, m+1, j, l, r, x);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	ll query(int node, int i, int j, int l, int r) {
		flush(node, i, j);
		if(i > r || j < l)
			return 0;
		if(i >= l && j <= r)
			return tree[node];
		int m = (i+j) >> 1;
		return query(2*node, i, m, l, r) + query(2*node+1, m+1, j, l, r);
	}
} seg;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		st.insert({i, i});
	while(m--) {
		int t, l, r; scanf("%d %d %d", &t, &l, &r);
		if(t==1) {
			int x; scanf("%d", &x);
			auto it = st.lower_bound({l, 0});
			auto prev_it = it;
			int cor, last = l;
			if(l==1) cor = 1;
			else cor = (*(--prev_it)).ss;
			vector<pii> rm;
			while(it != st.end() && (*it).ff <= r) {
				if((*it).ff != l)
					seg.upd(1, 1, n, last, (*it).ff-1, abs(x - cor));
				last = (*it).ff;
				cor = (*it).ss;
				rm.pb(*it);
				++it;
			}
			seg.upd(1, 1, n, last, r, abs(x - cor));
			for(pii R : rm)
				st.erase(R);
			st.insert({l, x});
			if(st.lower_bound({r+1, 0}) == st.end() || (*st.lower_bound({r+1, 0})).ff != r+1)
				st.insert({r+1, cor});
		} else printf("%lld\n", seg.query(1, 1, n, l, r));
	}
}