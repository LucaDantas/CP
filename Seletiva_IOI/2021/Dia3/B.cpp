#include <bits/stdc++.h>
using namespace std;

#define l first
#define r second

constexpr int maxn = 1e5+10;

pair<int,int> a[maxn];

struct BIT
{
	int bit[maxn];
	void upd(int x, int v) {
		for(; x > 0; x -= x&-x)
			bit[x] = max(v, bit[x]);
	}
	int query(int x) {
		int ans = 0;
		for(; x < maxn; x += x&-x)
			ans = max(ans, bit[x]);
		return ans;
	}
} bit;

map<int,int> mp;

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &a[i].l, &a[i].r);
		if(a[i].l > a[i].r)
			swap(a[i].l, a[i].r);
		mp[a[i].r];
	}
	int coord = 0;
	for(auto& it : mp)
		it.second = ++coord;
	sort(a, a+n, greater<pair<int,int>>());
	int ans = 0;
	for(int i = 0; i < n; i++) {
		int v = a[i].r;
		int here = bit.query(mp[v])+1;
		ans = max(ans, here);
		bit.upd(mp[v], here);
	}
	printf("%d\n", ans);
}