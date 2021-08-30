#include <cstdio>

constexpr int maxn = 1e5+10, logn = 18;

long long min(long long a, long long b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }

long long p[maxn];

struct ST {
	long long a[maxn][logn][2];
	void build(long long n) {
		for(int i = 0; i < n; i++)
			a[i][0][0] = a[i][0][1] = p[i];
		for(int j = 1; j < logn; j++)
			for(int i = 0; i + (1 << j) - 1 < n; i++)
				a[i][j][0] = min(a[i][j-1][0], a[i+(1<<(j-1))][j-1][0]),
				a[i][j][1] = max(a[i][j-1][1], a[i+(1<<(j-1))][j-1][1]);
	}
	long long mn(int l, int r) {
		int sz = r-l+1, lg = 31-__builtin_clz(sz);
		return min(a[l][lg][0], a[r-(1<<lg)][lg][0]);
	}
	long long mx(int l, int r) {
		int sz = r-l+1, lg = 31-__builtin_clz(sz);
		return max(a[l][lg][1], a[r-(1<<lg)][lg][1]);
	}
} st;

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 0; i < n; i++)
		scanf("%lld", &p[i]);
	for(int i = 0, v; i < n; i++)
		scanf("%d", &v), p[i] -= v, p[i] += i ? p[i-1] : 0;
	st.build(n);
	/* for(int i = 0; i < n; i++)
		fprintf(stderr, "%lld ", p[i]);
	fprintf(stderr, "\n"); */
	while(q--) {
		int l, r; scanf("%d %d", &l, &r); --l, --r;
		// fprintf(stderr, "DB %lld %lld | %lld %lld\n", l, r, st.mx(l, r), st.mn(l, r));
		if((l ? p[l-1] : 0) != p[r] || st.mx(l, r) > p[r]) { puts("-1"); continue; }
		printf("%lld\n", p[r] - st.mn(l, r));
	}
}
