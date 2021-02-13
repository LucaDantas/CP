#include<cstdio>
#include<utility>
#include<queue>
#include<cassert>
using namespace std;

constexpr int maxn = 2e5+10;

struct Line
{
	long long a, b; // ax + b
	Line(long long x, long long y) : a(x), b(y) {}
	long long intersection(Line L) {
		return (L.b-b)/(a-L.a);
	}
	long long val(long long x) {
		return a*x + b;
	}
};

deque<Line> hull; // hull ta ordenado por slope

void insert(Line L) {
	while(hull.size() >= 2 && L.intersection(hull.back()) < hull.back().intersection(hull[(int)hull.size()-2]))
		hull.pop_back();
	hull.push_back(L);
}

Line query(long long x) {
	while(hull.size() >= 2 && hull[0].val(x) >= hull[1].val(x))
		hull.pop_front();
	return hull[0];
}

long long dp, a, C;

int main() {
	int n; scanf("%d %lld", &n, &C);
	scanf("%lld", &a);
	hull.push_back(Line(-2*a, a*a));
	for(int i = 1; i < n; i++) {
		scanf("%lld", &a);
		dp = a*a + C + query(a).val(a);
		insert(Line(-2*a, dp + a*a));
	}
	printf("%lld\n", dp);
}