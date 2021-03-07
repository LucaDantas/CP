#include<cstdio>
#include<vector>
#include<algorithm>

constexpr int maxn = 2e3+10, maxm = 2e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct BIT
{
	long long bit[maxn][maxn];
	void init() {
		for(int i = 0; i < maxn; i++)
			for(int j = 0; j < maxn; j++)
				bit[i][j] = -inf;
	}
	void upd(int x, int y, long long v) {
		for(int i = x; i < maxn; i += i&-i)
			for(int j = y; j < maxn; j += j&-j)
				bit[i][j] = std::max(bit[i][j], v);
	}
	long long query(int x, int y) {
		long long ans = -inf;
		for(int i = x; i > 0; i -= i&-i)
			for(int j = y; j > 0; j -= j&-j)
				ans = std::max(ans, bit[i][j]);
		return ans;
	}
} bit;

int a[maxn];

struct Query
{
	int l, r, id; long long u;
	bool operator<(const Query& q) { return u < q.u; }
};

struct Range
{
	int l, r; long long sum;
	bool operator<(const Range& q) { return sum < q.sum; }
};

long long ans[maxm];

std::vector<Range> v;
std::vector<Query> queries;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) {
		int l, r; long long v;
		scanf("%d %d %lld", &l, &r, &v);
		queries.push_back({l, r, i, v});
	}
	bit.init();
	for(int i = 0; i < m; i++)
		ans[i] = -inf;
	for(int i = 1; i <= n; i++) {
		long long sum = 0;
		for(int j = i; j <= n; j++) {
			sum += a[j];
			v.push_back({i, j, sum});
		}
	}
	std::sort(queries.begin(), queries.end());
	std::sort(v.begin(), v.end());
	for(int i = 0, ptr = 0; i < m; i++) {
		while(ptr < (int)v.size() && v[ptr].sum <= queries[i].u) {
			bit.upd(n - v[ptr].l + 1, v[ptr].r, v[ptr].sum);
			++ptr;
		}
		ans[queries[i].id] = bit.query(n - queries[i].l + 1, queries[i].r);
	}
	for(int i = 0; i < m; i++) {
		if(ans[i] == -inf) puts("NONE");
		else printf("%lld\n", ans[i]);
	}
}