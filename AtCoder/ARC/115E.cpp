#include <cstdio>
#include <vector>
#include <utility>
#include <cassert>

constexpr int maxn = 5e5+10, mod = 998244353;

std::vector<std::pair<int,int>> grps;

int mul(int x, int y) { return (int)(1ll * x * y % mod); }

int pref[maxn];

int get(int l, int r) {
	--l;
	if(l%2 == r%2) {
		int even = (pref[r] - (l>=0?pref[l]:0) + mod) % mod;
		int odd = (pref[r-1] - (l>=1?pref[l-1]:0) + mod) % mod;
		return (even - odd + mod) % mod;
	} else {
		int even = (pref[r] - (l>=1?pref[l-1]:0) + mod) % mod;
		int odd = (pref[r-1] - (l>=0?pref[l]:0) + mod) % mod;
		return (even - odd + mod) % mod;
	}
}

int main() {
	int n; scanf("%d", &n);
	int sum = 1;
	pref[0] = 1;
	for(int i = 1, last = 0; i <= n; i++) {
		int a; scanf("%d", &a);
		if(a >= last) {
			if(a > last)
				grps.push_back({last+1, i-1});
			sum = mul(sum, a - 1 + (i==1));
		} else {
			sum = mul(sum, last - 1);
			while(grps.size() && grps.back().first > a) {
				sum -= (mul(get(grps.back().second, i-1), (last - grps.back().first + 1)) + mod) % mod;
				if(sum < 0) sum += mod;
				last = grps.back().first - 1; grps.pop_back();
			}
			sum -= (mul(get(grps.back().second, i-1), (last - a)) + mod) % mod;
			if(sum < 0) sum += mod;
		}
		last = a;
		pref[i] = (sum + (i>=2?pref[i-2]:0)) % mod;
	}
	printf("%d\n", sum);
}
