#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

constexpr int maxn = 1e6+10, inf = 0x3f3f3f3f;

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

struct Node
{
	int l, r, k;
} node[maxn];

struct Event
{
	int t, id, x;
	bool operator<(Event e) { if(x == e.x) return t < e.t; return x < e.x;}
};

struct Query
{
	int l, r;
} queries[maxn];

int ans[maxn], mn[maxn], mx[maxn];

void dfs(int u) {
	if(!u) return;
	dfs(node[u].l);
	mn[u] = std::min(node[u].k, mn[node[u].l]);
	dfs(node[u].r);
	mx[u] = std::max(node[u].k, mx[node[u].r]);
}

int main() {
	std::map<int,int> mp;
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int l, r, k; scanf("%d %d %d", &l, &r, &k);
		node[i] = {l, r, k}; mp[k];
	}
	mn[0] = inf;
	mx[0] = -inf;
	dfs(1);
	std::vector<Event> ev;
	for(int i = 1; i <= n; i++) {
		ev.push_back({-1, mn[i], mn[i]}), ev.push_back({1, mn[i], mx[i]});
	}
	int q; scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		int l, r; scanf("%d %d", &l, &r);
		queries[i] = {l, r};
		mp[l], mp[r];
		ev.push_back({-2, i, l});
		ev.push_back({2, i, r});
	}
	std::sort(ev.begin(), ev.end());
	int coord = 0;
	for(auto& it : mp)
		it.second = ++coord;
	for(auto e : ev) {
		if(e.t == -1 || e.t == 1) bit.upd(mp[e.id], -e.t);
		else if(e.t == -2) ans[e.id] += bit.query(coord);
		else ans[e.id] += bit.query(coord) - bit.query(mp[queries[e.id].l]-1);
	}
	for(int i = 0; i < q; i++)
		printf("%d\n", 2*ans[i]+1);
}