#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll,ll>;

#define pb push_back
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 1e5+10;

int a[maxn], back[30];
long long soma[maxn];

ll sum(int l, int r) { return soma[r] - soma[l-1]; }

map<int, int> mp;

long long ans[maxn];

struct Query
{
	int l, r;
} queries[maxn], itv[maxn];

struct Event
{
	int t, x, id;
	bool operator<(Event e) {
		if(x == e.x) return t < e.t;
		return x < e.x;
	}
};

struct SegmentTreeLazy
{
	int tree[4*maxn];
	void upd(int node, int i, int j, int l, int r, int v) {
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(tree[node] = max(tree[node], v));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, v);
		upd(node<<1|1, m+1, j, l, r, v);
	}
	int query(int node, int i, int j, int pos) {
		if(i == j) return tree[node];
		int m = (i+j) >> 1;
		if(pos <= m) return max(tree[node], query(node<<1, i, m, pos));
		return max(tree[node], query(node<<1|1, m+1, j, pos));
	}
	void clear() { memset(tree, 0, sizeof tree); }
} seg1;

struct SegmentTreeNormal
{
	ll tree[4*maxn];
	void upd(int node, int i, int j, int pos, ll v) {
		if(i == j) return (void)(tree[node] = max(tree[node], v));
		int m = (i+j) >> 1;
		if(pos <= m) upd(node<<1, i, m, pos, v);
		else upd(node<<1|1, m+1, j, pos, v);
		tree[node] = max(tree[node<<1], tree[node<<1|1]);
	}
	ll query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		ll ans = query(node<<1, i, m, l, r);
		ans = max(ans, query(node<<1|1, m+1, j, l, r));
		return ans;
	}
	void clear() { memset(tree, 0, sizeof tree); }
} seg2;

vector<Event> events[30];

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]); mp[a[i]];
		soma[i] = soma[i-1] + a[i];
	}
	int coord = 0;
	for(auto& it : mp)
		it.second = ++coord, back[coord] = it.first;

	stack<int> st;
	for(int i = 1; i <= n; i++) {
		while(st.size() && a[i] <= a[st.top()]) {
			int id = st.top();
			st.pop();
			itv[id] = {st.size()?st.top()+1:1, i-1};
			events[mp[a[id]]].pb({-1, st.size()?st.top()+1:1, id});
			events[mp[a[id]]].pb({1, i-1, id});
		}
		st.push(i);
	}
	while(st.size()) {
		int id = st.top();
		st.pop();
		itv[id] = {st.size()?st.top()+1:1, n};
		events[mp[a[id]]].pb({-1, st.size()?st.top()+1:1, id});
		events[mp[a[id]]].pb({1, n, id});
	}

	for(int i = 0; i < q; i++)
		scanf("%d %d", &queries[i].l, &queries[i].r);

	for(int i = 1; i <= coord; i++) {
		for(int id = 0; id < q; id++)
			events[i].pb({2, queries[id].r, id});
		sort(all(events[i]));
		multiset<int> st;
		for(auto e : events[i]) {
			auto [t, x, id] = e;
			if(t == -1) st.insert(x);
			if(t == 1) {
				int l = itv[id].l;
				st.erase(st.find(l));
				seg1.upd(1, 1, n, l, x, x);
				seg2.upd(1, 1, n, l, 1ll*back[i]*sum(l, x));
			}
			if(t == 2) {
				auto [l, r] = queries[id];
				if(st.size()) {
					int pos = max(l, *st.begin());
					ans[id] = max(ans[id], 1ll*back[i]*sum(pos, r));
				}

				int pos = seg1.query(1, 1, n, l);
				if(pos)
					ans[id] = max(ans[id], 1ll*back[i]*sum(l,pos));
				
				ans[id] = max(ans[id], seg2.query(1, 1, n, l, r));
			}
		}
		seg1.clear();
		seg2.clear();
		st.clear();
	}
	for(int i = 0; i < q; i++)
		printf("%lld\n", ans[i]);
}