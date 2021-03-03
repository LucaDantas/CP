#include<cstdio>
#include<vector>
#include <algorithm>
#include<utility>

constexpr int maxn = 1e5+10, B = 1000, maxB = 110; // block sz

struct BIT
{
	int bit[maxB][maxn], n;
	void upd(int x, int y) {
		for(int i = x+1; i < maxB; i += i&-i)
			for(int j = y; j < maxn; j += j&-j)
				bit[i][j]++;
	}
	int query(int x, int y) {
		int ans = 0;
		for(int i = x+1; i > 0; i -= i&-i)
			for(int j = y; j > 0; j -= j&-j)
				ans += bit[i][j];
		return ans;
	}
} bit;

struct Query
{
	int x, y, z, id;
	Query(int a, int b, int c, int sla) : x(a), y(b), z(c), id(sla) {}
	Query() {}
} queries[maxn];

struct Pt
{
	int x, y, sum;
	Pt(int a, int b) : x(a), y(b), sum(a+b) {}
	Pt() {}
} a[maxn];

std::vector<std::pair<int,int>> comp[2];
std::vector<Pt> bloco[maxB];

int ans[maxn];

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 0, x, y; i < n; i++) {
		scanf("%d %d", &x, &y);
		a[i] = Pt(x, y);
		comp[0].push_back({x, i});
		comp[1].push_back({y, i});
	}
	std::sort(comp[0].begin(), comp[0].end());
	std::sort(comp[1].begin(), comp[1].end());
	for(int i = 0; i < q; i++) {
		int x, y, z; scanf("%d %d %d", &x, &y, &z);
		auto l = lower_bound(comp[0].begin(), comp[0].end(), std::pair<int,int>(x, -1));
		x = (int)(l - comp[0].begin() + 1);
		l = lower_bound(comp[1].begin(), comp[1].end(), std::pair<int,int>(y, -1));
		y = (int)(l - comp[1].begin() + 1);
		queries[i] = Query(x, y, z, i);
	}
	for(int i = 0; i < (int)comp[0].size(); i++)
		a[comp[0][i].second].x = i+1;
	for(int i = 0; i < (int)comp[1].size(); i++)
		a[comp[1][i].second].y = i+1;

	std::sort(a, a+n, [](Pt x, Pt y){ return x.sum > y.sum; });
	std::sort(queries, queries+q, [](Query x, Query y){ return x.z > y.z; });
	for(int i = 0, ptr = 0; i < q; i++) {
		for(; ptr < n && a[ptr].sum >= queries[i].z; ptr++)
			bit.upd(a[ptr].x / B, a[ptr].y), bloco[a[ptr].x / B].push_back(a[ptr]);

		ans[queries[i].id] = ptr + bit.query((queries[i].x / B), queries[i].y-1)
		- bit.query(maxB - 2, queries[i].y-1) - bit.query((queries[i].x / B), maxn-1);
		for(Pt x : bloco[queries[i].x / B])
			if(x.x >= queries[i].x && x.y >= queries[i].y) ++ans[queries[i].id];
	}

	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}