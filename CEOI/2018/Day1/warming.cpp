#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

constexpr int maxn = 2e5+10;

int coord = 0;
std::map<int,int> mp;

void build() {
	coord = 0;
	for(auto& x : mp)
		x.second = ++coord;
}

int norm(int x) {
	auto k = mp.upper_bound(x);
	if(k == mp.end()) return coord;
	return k->second-1;
}

struct BIT {
	int bit[maxn];
	void upd(int x, int v) {
		x = norm(x);
		for(x++; x < maxn; x += x&-x)
			bit[x] = std::max(bit[x], v);
	}
	int query(int x) {
		int ans = 0;
		x = norm(x);
		for(x++; x > 0; x -= x&-x)
			ans = std::max(ans, bit[x]);
		return ans;
	}
	void clear() { memset(bit, 0, sizeof bit); }
} bit;

int t[maxn], dp[maxn], max_temp;

int main() {
	int n, x; scanf("%d %d", &n, &x);
	for(int i = 0; i < n; i++)
		scanf("%d", t+i), max_temp = std::max(max_temp, t[i]), mp[t[i]] = 0;
	build();

	for(int i = 0; i < n; i++) {
		dp[i] = bit.query(t[i]-1)+1;
		bit.upd(t[i], dp[i]);
	}

	bit.clear();

	int ans = 0;
	std::reverse(t, t+n);
	std::reverse(dp, dp+n);
	mp.clear();
	for(int i = 0; i < n; i++)
		t[i] = max_temp - t[i] + 1, mp[t[i]] = 0;
	build();

	for(int i = 0; i < n; i++) {
		ans = std::max(ans, dp[i] + bit.query(t[i] + x - 1));
		bit.upd(t[i], bit.query(t[i]-1)+1);
	}

	printf("%d\n", ans);
}
