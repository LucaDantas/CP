#include <bits/stdc++.h>
using namespace std;

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	long long n, A, B; scanf("%lld %lld %lld", &n, &A, &B);
	long long g = __gcd(A, B+1), sz = 0;
	if(log(A) + log(B) - log(g) > log(inf)) sz = inf;
	else sz = (A/g) * B;
	vector<pair<long long, long long>> pares;
	long long ini = 0, fim = -1, ans = 0;
	for(int i = 0; i < n; i++) {
		long long l, r; scanf("%lld %lld", &l, &r);
		if(r - l + 1 >= sz) return printf("%lld\n", sz), 0;
		l %= sz, r %= sz;
		if(r < l) fim = max(fim, r), pares.push_back({l, sz-1});
		else pares.push_back({l, r});
	}
	sort(pares.begin(), pares.end());
	for(auto p : pares) {
		if(p.first > fim) ans += fim - ini+1, ini = p.first, fim = p.second;
		else fim = max(fim, p.second);
	}
	printf("%lld\n", ans + fim - ini + 1);
}
