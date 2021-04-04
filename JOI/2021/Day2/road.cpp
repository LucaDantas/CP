#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(a) (a).begin(), (a).end()

constexpr int maxn = 3e5+10;
constexpr ll inf = 0xffffffff;

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(x++; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(x++; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
	int get(int l, int r) { return query(r) - query(l-1); }
	void clear() { memset(bit, 0, sizeof bit); }
} bit;

struct Pt
{
	ll x, y; int pos;
	bool operator<(Pt p) { if(x == p.x) return y < p.y; return x < p.x; }
};

vector<Pt> a;

int n;
vector<pair<ll,int>> comp; // compressed y coordenate

int first_pos(ll v) { return lower_bound(all(comp), pair<ll,int>(v, 0)) - comp.begin(); }

int last_pos(ll v) { return upper_bound(all(comp), pair<ll,int>(v, maxn)) - comp.begin() - 1; }

ll get(ll lim) {
	bit.clear();
	ll ans = 0;
	for(int i = 0, ptr = 0; i < n; i++) {
		for(; ptr < n && a[ptr].x <= a[i].x + lim; ptr++)
			bit.upd(a[ptr].pos, 1);
		bit.upd(a[i].pos, -1);
		ans += bit.get(first_pos(a[i].y - lim), last_pos(a[i].y + lim));
	}
	return ans;
}

int main() {
	int k; scanf("%d %d", &n, &k);
	// Rotate the points to map the manhattan distance to chebyshev distance
	for(int i = 0, x, y; i < n; i++)
		scanf("%d %d", &x, &y), a.push_back({x+y, x-y, 0}), comp.push_back({x-y, i});
	sort(all(comp));
	for(int i = 0; i < n; i++)
		a[comp[i].second].pos = i;
	sort(all(a));
	ll l = 0, r = inf, lim = 0;
	while(l <= r) {
		ll m = (l+r) >> 1;
		if(get(m) >= k) lim = m, r = m-1;
		else l = m+1;
	}
	multiset<pair<ll,ll>> st;
	vector<ll> ans;
	auto dist = [](pair<ll,ll> a, pair<ll,ll> b) {
		return max(abs(a.first - b.first), abs(a.second - b.second));
	};
	for(int i = 0, ptr = 0; i < n; i++) {
		for(; ptr < n && a[ptr].x < a[i].x + lim; ptr++)
			st.insert({a[ptr].y, a[ptr].x});
		st.erase(st.find({a[i].y, a[i].x}));
		auto it = st.upper_bound({a[i].y - lim, inf}); // quero as respostas estritamente menores q ans
		for(;it != st.end() && (*it).first < a[i].y + lim; ++it)
			ans.push_back(dist(*it, {a[i].y, a[i].x}));
	}
	while((int)ans.size() < k)
		ans.push_back(lim);
	sort(all(ans));
	for(ll x : ans)
		printf("%lld\n", x);
}