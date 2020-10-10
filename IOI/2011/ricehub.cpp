#include "ricehub.h"
#include<algorithm>

using ll = long long;

constexpr int maxn = 1e5+10;

ll pref[maxn];

inline ll itv(int l, int r) { return pref[r] - (l?pref[l-1]:0); }

ll cost(int l, int r, int a[]) {
	if(l == r) return 0;
	int m = (l+r) >> 1;
	int pos = a[m];
	ll cost = 1ll*pos*(m-l+1) - itv(l, m);
	cost += itv(m+1, r) - 1ll*pos*(r-m);
	return cost;
}

int besthub(int n, int l, int a[], ll b)
{
	int ans = 0;
	pref[0] = a[0];
	for(int i = 1; i < n; i++)
		pref[i] = pref[i-1]+a[i];
	for(int i = 0; i < n; i++) {
		int l = i, r = n-1, best = -1;
		while(l <= r) {
			int m = (l+r) >> 1;
			if(cost(i, m, a) <= b)
				best = m, l = m+1;
			else
				r = m-1;
		}
		ans = std::max(ans, best - i + 1);
	}
	return ans;
}
