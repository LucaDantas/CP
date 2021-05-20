#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

#define pb push_back

int x, y, k, d[maxn], coord, qtd;

map<int,int> mp;

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
	void itv(int l, int r) { if(r - l < 1) return; upd(l, 1); upd(r+1, -1); }
	void clear() { memset(bit, 0, sizeof bit); }
} bit;

struct Event
{
	int t, x, y0, y1;
	bool operator<(Event e) { if(x == e.x) return t > e.t; return x < e.x; }
};

bool check(int n) {
	vector<Event> events;
	x = y = qtd = 0;
	for(int i = 1; i <= n; i++) {
		if(i&1) {
			int x0 = x, x1 = x+d[i];
			if(x0 > x1) swap(x0, x1);
			events.pb({-1, x0, y, 0});
			events.pb({1, x1, y, 0});
			x += d[i];
		}
		else {
			int y0 = y, y1 = y+d[i];
			if(y0 > y1) swap(y0, y1);
			events.pb({0, x, y0, y1});
			y += d[i];
		}
	}
	sort(events.begin(), events.end());
	bit.clear();
	for(auto e : events) {
		auto [t, x, y0, y1] = e;
		y0 = mp[y0];
		y1 = mp[y1];
		if(t) qtd += t * bit.query(y0);
		else bit.itv(y0, y1);
	}
	return qtd < k;
}

int main() {
	int n; scanf("%d %d", &n, &k);
	mp[0];
	for(int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
		if(i&1) x += d[i];
		else y += d[i], mp[y];
	}
	for(auto& it : mp)
		it.second = ++coord;
	int l = 0, r = n, ans = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(check(m)) l = m+1, ans = m;
		else r = m-1;
	}
	++ans; // acho na bb o ultimo menor q k
	ans = min(ans, n);
	check(ans);
	printf("%d %d\n", ans, qtd);
}