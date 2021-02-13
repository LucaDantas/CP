#include<cstdio>
#include<deque>
#include<utility>
#include<algorithm>

constexpr int maxn = 1e6+10;

struct Line
{
	long long a, b; // ax + b
	Line(long long _a, long long _b) : a(_a), b(_b) {}
	Line() {}
	long long val(long long x) { return a*x + b; }
	long double intersect(Line L) { return (long double)(L.b-b)/(a-L.a); }
};

struct CHT
{
	std::deque<Line> hull;
	void insert(Line L) {
		while(hull.size() >= 2 && L.intersect(hull.back())
			>= L.intersect(hull[(int)hull.size()-2]))
			hull.pop_back();
		hull.push_back(L);
	}
	Line query(long long x) {
		while(hull.size() >= 2 && hull[0].val(x) <= hull[1].val(x))
			hull.pop_front();
		return hull.front();
	}
} cht;

std::pair<std::pair<long long,long long>,long long> rec[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		long long x, y, a; scanf("%lld %lld %lld", &x, &y, &a);
		rec[i] = {{y, x}, a};
	}
	std::sort(rec, rec+n);
	long long dp = 0, ans = 0;
	cht.insert(Line(0, 0));
	for(int i = 0; i < n; i++) {
		long long x = rec[i].first.second, y = rec[i].first.first;
		long long a = rec[i].second;
		dp = x*y - a + cht.query(x).val(x);
		ans = std::max(ans, dp);
		cht.insert(Line(-y, dp));
	}
	printf("%lld\n", ans);
}
