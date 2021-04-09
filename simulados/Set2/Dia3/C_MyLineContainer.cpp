#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll,ll>;

#define a first
#define b second
#define pb push_back
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 2e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct Line
{
	long long a, b, x; // vou codar com inteiros msm
	Line(long long _a = 0, long long _b = 0, long long _x = inf) : a(_a), b(_b), x(_x) {}
	bool operator<(const Line& o) const { return a < o. a; } // change < for >, for min queries
	bool operator<(const long long& o) const { return x < o; }
};

struct LineContainer : multiset<Line, less<>>
{
	bool hasNext(iterator it) { return next(it) != end(); }
	bool hasPrev(iterator it) { return it != begin(); }
	long long div(long long a, long long b) { return a / b - ((a^b)<0 && a%b); }
	long long intersect(Line l1, Line l2) { return div(l1.b-l2.b, l2.a-l1.a); }
	bool bad(Line l1, Line l2, Line l3) { return intersect(l1, l3) <= intersect(l1, l2); }
	iterator get_x(iterator it) {
		if(!hasNext(it)) return it;
		Line l = *it;
		l.x = intersect(l, *next(it));
		erase(it);
		return insert(l);
	}
	void add(long long a, long long b) {
		Line l(a, b);
		auto it = lower_bound(l);
		if(it != end() && it->a == a) {
			if(it->b >= b) return;
			erase(it);
		}
		it = insert(l);
		if(hasPrev(it) && hasNext(it) && bad(*prev(it), *it, *next(it)))
			return (void)(erase(it));
		while(hasPrev(it) && hasPrev(prev(it)) && bad(*prev(prev(it)), *prev(it), *it))
			erase(prev(it));
		while(hasNext(it) && hasNext(next(it)) && bad(*it, *next(it), *next(next(it))))
			erase(next(it));
		it = get_x(it);
		if(hasPrev(it)) get_x(prev(it));
	}
	long long query(long long x) {
		if(empty()) return 0ll;
		auto it = lower_bound(x);
		return it->a*x + it->b;
	}
};

struct SegmentTree
{
	LineContainer tree[4*maxn];
	void upd(int node, int i, int j, int l, int r, const pii& L) {
		if(i > r || j < l) return;
		if(i >= l && j <= r) return (void)(tree[node].add(L.a, L.b));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, L);
		upd(node<<1|1, m+1, j, l, r, L);
	}
	ll query(int node, int i, int j, int pos, ll x) {
		if(i == j) return tree[node].query(x);
		int m = (i+j) >> 1;
		if(pos <= m) return max(tree[node].query(x), query(node<<1, i, m, pos, x));
		return max(tree[node].query(x), query(node<<1|1, m+1, j, pos, x));
	}
	void clear() { for(int i = 0; i < 4*maxn; i++) tree[i].clear(); }
} seg;

struct SegmentTreeNormal
{
	ll tree[4*maxn];
	void upd(int node, int i, int j, int pos, ll v, bool set = 0) {
		if(i == j) return (void)(tree[node] = set?v:max(tree[node], v));
		int m = (i+j) >> 1;
		if(pos <= m) upd(node<<1, i, m, pos, v, set);
		else upd(node<<1|1, m+1, j, pos, v, set);
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
} seg2, seg3;

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

vector<Event> events;

int a[maxn];
ll soma[maxn], ans[maxn], suf[maxn];

multiset<int> ativos[maxn];

ll sum(int l, int r) { return soma[r] - soma[l-1]; }

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		soma[i] = soma[i-1] + a[i];
	}
	for(int i = n; i >= 1; i--) {
		suf[i] = suf[i+1] + a[i];
	}

	stack<int> st;
	for(int i = 1; i <= n; i++) {
		while(st.size() && a[i] <= a[st.top()]) {
			int id = st.top();
			st.pop();
			itv[id] = {st.size()?st.top()+1:1, i-1};
			events.pb({-1, st.size()?st.top()+1:1, id});
			events.pb({1, i-1, id});
		}
		st.push(i);
	}
	while(st.size()) {
		int id = st.top();
		st.pop();
		itv[id] = {st.size()?st.top()+1:1, n};
		events.pb({-1, st.size()?st.top()+1:1, id});
		events.pb({1, n, id});
	}

	for(int i = 0; i < q; i++)
		scanf("%d %d", &queries[i].l, &queries[i].r),
		events.pb({2, queries[i].r, i});

	sort(all(events));

	for(auto& e : events) {
		auto [t, r, id] = e;
		if(t == -1) {
			int l = itv[id].l;
			ativos[l].insert(a[id]);
			seg3.upd(1, 1, n, l, *ativos[l].rbegin(), 1);
		}
		if(t == 1) {
			int l = itv[id].l;

			ativos[l].erase(ativos[l].find(a[id]));
			seg3.upd(1, 1, n, l, ativos[l].size()?*ativos[l].rbegin():0, 1);

			pii reta = {-a[id], a[id] * soma[r]};
			seg.upd(1, 1, n, l, r, reta);

			seg2.upd(1, 1, n, l, 1ll*a[id]*sum(l, r));

			e.x = -l + n + 1;
		}
		if(t == 2) {
			int l = queries[id].l;
			ans[id] = max(ans[id], seg.query(1, 1, n, l, soma[l-1]));

			ans[id] = max(ans[id], seg2.query(1, 1, n, l, r));

			ans[id] = max(ans[id], seg3.query(1, 1, n, 1, l) * sum(l, r));

			e.x = -l + n + 1;
		}
	}

	seg.clear();
	seg2.clear();

	sort(all(events));

	for(auto& e : events) {
		auto [t, r, id] = e;
		if(t == 1) {
			int l = n+1 - itv[id].r;
			pii reta = {-a[id], a[id] * suf[n+1-r]};
			seg.upd(1, 1, n, l, r, reta);
			e.x = itv[id].r;
		}
		if(t == 2) {
			int l = n+1 - queries[id].r;
			ans[id] = max(ans[id], seg.query(1, 1, n, l, suf[n+1-(l-1)]));
			e.x = itv[id].r;
		}
	}

	for(int i = 0; i < q; i++)
		printf("%lld\n", ans[i]);
}
