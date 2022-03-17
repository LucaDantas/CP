#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())

constexpr int maxn = 300+10, true_mod = 1<<30, bit_mod = true_mod-1; // mod vira x & mod, ao invés de x%mod pra operação ser mais rapida

long long ans = 0;

void add(ll& a, long long x) {
	if(x < 0) x += true_mod;
	a += x;
	a &= bit_mod;
	if(a < 0) a += true_mod;
}

vector<pair<int,int>> todos;

int n;

ll cnt[maxn];

int sinal(int x) { return x == (n-1)/2 ? 0 : x < (n-1)/2 ? -1 : 1; }

struct SegmentTree
{
	vector<int> tree[4*maxn*maxn];
	vector<vector<ll>> roolback;
	void upd(int node, int i, int j, int l, int r, int v) {
		if(i > r || j < l || r < l) return;
		if(i >= l && j <= r) return (void)(tree[node].pb(v));
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, v);
		upd(node<<1|1, m+1, j, l, r, v);
	}
	void build(int node, int i, int j) {
		if(!roolback.size()) {
			roolback.pb(vector<ll>(maxn, 0)), roolback[0][0] = 1;
		}
		vector<ll> dp = roolback.back(), new_dp(maxn, 0);
		for(int v : tree[node]) {
			new_dp[0] = dp[0] * (n - v) & bit_mod;
			for(int q = 1; q <= n; q++) {
				new_dp[q] = dp[q] * (n - v) & bit_mod;
				add(new_dp[q], dp[q-1] * v);
			}
			swap(dp, new_dp);
		}
		if(i == j) {
			long long aq = 0;
			for(int q = 0; q <= n; q++)
				add(aq, 1ll * todos[i].ff * dp[q] * sinal(q) % true_mod);
			add(ans, aq);
		} else {
			roolback.push_back(dp);
			int m = (i+j) >> 1;
			build(node<<1, i, m); build(node<<1|1, m+1, j);
			roolback.pop_back();
		}
	}
} seg;

int last[maxn];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 0, h; j < n; j++) {
			scanf("%d", &h); todos.pb({h, i});
		}
	}
	sort(all(todos));
	int pos = 0;
	for(auto p : todos) {
		auto [h, ind] = p;
		seg.upd(1, 0, n*n-1, last[ind], pos-1, cnt[ind]);
		++cnt[ind];
		last[ind] = ++pos;
	}
	for(int ind = 1; ind <= n; ind++)
		seg.upd(1, 0, n*n-1, last[ind], n*n-1, cnt[ind]);
	seg.build(1, 0, n*n-1);
	printf("%lld\n", ans);
}
