#include <cstdio>
#include <vector>
#include <algorithm>

long long solve(std::vector<long long> a) {
	if(a.size() == 1) return a[0];
	if(!a.size()) return 0;

	int n = (int)(a.size());
	std::vector<long long> l, r;
	for(int i = 0; i < (n >> 1); i++)
		l.push_back(a[i]);
	for(int i = (n >> 1); i < n; i++)
		r.push_back(a[i]);

	long long ans = std::max(solve(l), solve(r));

	std::vector<std::pair<long long,int>> L, R;
	std::reverse(l.begin(), l.end());

	for(int k = 0; k < 2; k++, std::swap(L, R), std::swap(l, r)) {
		long long gcd = l[0];
		int sz = 1;
		for(int i = 1; i < (int)(l.size()); i++) {
			if(std::__gcd(gcd, l[i]) != gcd) L.push_back({gcd, sz});
			gcd = std::__gcd(gcd, l[i]); sz++;
		}
		L.push_back({gcd, sz});
	}

	for(auto x : L) for(auto y : R)
		ans = std::max(ans, std::__gcd(x.first, y.first) * (x.second + y.second));

	/* fprintf(stderr, "DEBUG:");
	for(long long x : a)
		fprintf(stderr, " %lld", x);
	fprintf(stderr, " -> %lld\n", ans); */

	return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		std::vector<long long> a(n);
		for(long long& x : a)
			scanf("%lld", &x);
		printf("%lld\n", solve(a));
	}
}
