#include <cstdio>
#include <algorithm>
#include <cstring>

constexpr int maxn = 2010;
constexpr int maxn2 = 100010;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct Order { int c, f, v; bool operator<(Order o) const { if(f != o.f) return f < o.f; return c > o.c; } };

Order td[maxn<<1];

long long dp[2][maxn2];

void max_self(long long& a, long long b) { a = std::max(a, b); }

int main() {
	int n; scanf("%d", &n);
	for(int i = 0, c, f, v; i < n; i++)
		scanf("%d %d %d", &c, &f, &v), td[i] = {-c, f, -v};

	int m, sum = 0; scanf("%d", &m);
	for(int i = n, c, f, v; i < n+m; i++)
		scanf("%d %d %d", &c, &f, &v), td[i] = {c, f, v}, sum += c;

	std::sort(td, td+n+m);

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < maxn2; j++)
			dp[i][j] = -inf;

	dp[0][0] = 0;

	for(int i = 0; i < n+m; i++) {
		for(int abertas = 0; abertas <= sum; abertas++)
			if(abertas + td[i].c <= sum)
				max_self(dp[i&1^1][std::max(0, abertas + td[i].c)], dp[i&1][abertas] + td[i].v),
				max_self(dp[i&1^1][abertas], dp[i&1][abertas]);
	}

	printf("%lld\n", dp[(n+m)&1][0]);
}
