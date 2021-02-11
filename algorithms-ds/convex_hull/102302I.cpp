#include<cstdio>
#include<set>
#include<map>
using namespace std;

constexpr int maxn = 1e5+10;

long long cross(pair<int, int> a, pair<int, int> b) {
	return 1ll*a.first*b.second-1ll*a.second*b.first;
}

bool ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	b.first -= a.first, b.second -= a.second;
	c.first -= a.first, c.second -= a.second;
	return cross(b, c) > 0;
}

map<int,int> cnt;

int main() {
	int n; scanf("%d", &n);

	set<pair<int,int>> hull;

	for(int i = 1; i <= n; i++) {
		pair<int,int> pt; scanf("%d %d", &pt.first, &pt.second);
		auto it = hull.upper_bound(pt);

		++cnt[pt.first];

		if(it == hull.end() || (it != hull.begin() && !ccw(*prev(it), pt, *it)) ||
			(it == hull.begin() && (*it).second <= pt.second)) {
			it = hull.insert(pt).first;

			while(it != hull.begin() && prev(it) != hull.begin() &&
				ccw(*prev(prev(it)), *prev(it), *it))
					hull.erase(prev(it));

			while(next(it) != hull.end() && next(next(it)) != hull.end() &&
				ccw(*it, *next(it), *next(next(it))))
					hull.erase(next(it));
		}
		
		while(hull.size() >= 2 && (*hull.begin()).second < (*next(hull.begin())).second)
			hull.erase(hull.begin());

		int edge = (int)cnt[(*hull.rbegin()).first]-1;
		printf("%d\n", i-(int)hull.size()-edge);
	}
}