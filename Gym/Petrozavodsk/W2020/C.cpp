#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

std::priority_queue<long long> q;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, d; scanf("%d %d", &n, &d);
		long long shift = 0, ans = 0;
		std::vector<long long> a(n);
		for(long long& x : a)
			scanf("%lld", &x);
		std::sort(a.begin(), a.end());
		for(long long x : a) {
			x -= shift;
			if(x < 0) ans -= x, x = 0;
			q.push(x); q.push(x);
			if(x < q.top())
				ans += q.top() - x;
			q.pop();
			shift += d;
		}
		printf("%lld\n", ans);
		while(q.size()) q.pop();
	}
}