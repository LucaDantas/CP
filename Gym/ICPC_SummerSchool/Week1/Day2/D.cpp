#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

bitset<maxn> a, b, ans;

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		a.reset(), b.reset(), ans.reset();
		vector<int> A(n);
		a.set(0);
		for(int& x : A)
			scanf("%d", &x), a.set(x);
		int m; scanf("%d", &m);
		vector<int> B(m);
		for(int& x : B)
			scanf("%d", &x), b.set(x);
		for(int x : A)
			ans |= ((a << x) & b);
		printf("%ld\n", ans.count());
	}
}
