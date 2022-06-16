#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, logn = 20;

int a[maxn], l[maxn][logn], r[maxn][logn];

int main() {
	int n, k, q; scanf("%d %d %d", &n, &k, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", a+i);

	l[1][0] = 1;
	for(int i = 2; i <= n; i++) {
		l[i][0] = i-1;
		while(a[l[i][0]] < a[i])
			l[i][0] = l[l[i][0]][0];
	}

	r[n][0] = n;
	for(int i = n-1; i >= 1; i--) {
		r[i][0] = i+1;
		while(a[r[i][0]] < a[i])
			r[i][0] = r[r[i][0]][0];
	}

	for(int lg = 1; lg < logn; lg++) {
		for(int i = 1; i <= n; i++) {
			l[i][lg] = min(l[l[i][lg-1]][lg-1], l[r[i][lg-1]][lg-1]);
			r[i][lg] = max(r[l[i][lg-1]][lg-1], r[r[i][lg-1]][lg-1]);
		}
	}

	while(q--) {
		int x, y; scanf("%d %d", &x, &y);
		if(x > y) swap(x, y);
		int L = x, R = x, ans = 0;
		for(int lg = logn-1; lg >= 0; lg--) if(max(r[L][lg], r[R][lg]) < y) {
			ans += 1<<lg;
			tie(L, R) = make_pair(min(l[L][lg], l[R][lg]), max(r[L][lg], r[R][lg]));
		}

		x = R;
		L = y, R = y;
		for(int lg = logn-1; lg >= 0; lg--) if(min(l[L][lg], l[R][lg]) > x) {
			ans += 1<<lg;
			tie(L, R) = make_pair(min(l[L][lg], l[R][lg]), max(r[L][lg], r[R][lg]));
		}
		printf("%d\n", ans);
	}
}
