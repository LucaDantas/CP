#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;


struct Event {
	int x, ini, t, id;
	bool operator<(const Event& o) const {
		if(x == o.x) return t < o.t;
		return x < o.x;
	}
};

struct BIT {
	int bit[maxn];
	void upd(int x, int v) {
		for(; x > 0; x -= x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x < maxn; x += x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

vector<Event> events;

int ans[maxn];
int x[maxn], h[maxn], a[maxn], b[maxn];

int main() {
	int n; scanf("%d", &n); if(n > 10000) assert(0);
	int Q; scanf("%d", &Q);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &x[i], &h[i]);
	x[0] = x[1];
	x[n+1] = x[n];
	for(int i = 1; i <= n; i++) {
		for(a[i] = i; a[i] > 0; --a[i]) {
			if(x[i] - x[a[i]-1] >= h[i]) break;
			if(x[i] - x[a[i]] >= h[a[i]]) a[i] = a[a[i]];
			if(x[i] - x[a[i]-1] >= h[i] || !a[i]) break;
		}
		fprintf(stderr, "a[i] %d %d\n", i, a[i]);
		// events.push_back({i, a[i], 1, i});
	}
	for(int i = n; i >= 1; i--) {
		for(b[i] = i; b[i] <= n; b[i]++) {
			if(x[b[i]] - x[i] >= h[i]) break;
			if(x[b[i]] - x[i] >= h[b[i]]) b[i] = b[b[i]];
			if(x[b[i]] - x[i] >= h[i] || b[i] > n) break;
		}
		fprintf(stderr, "b[i] %d %d\n", i, b[i]);
		/* events.push_back({b[i], i, 1, i});
		events.push_back({b[i], a[i], -1, i}); */
	}
	/* for(int qq = 0; qq < Q; qq++) {
		int l, r; scanf("%d %d", &l, &r);
		events.push_back({r, l, 2, qq});
	}
	sort(events.begin(), events.end());
	for(auto e : events) {
		int ini = e.ini, t = e.t, id = e.id;
		printf("%d %d %d %d\n", e.x, ini, t, id);
		if(t != 2) bit.upd(ini, t);
		else ans[id] = bit.query(ini);
	}
	for(int i = 0; i < Q; i++)
		printf("%d\n", ans[i]); */
}
