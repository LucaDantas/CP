#include <cstdio>
#include <utility>
#include <algorithm>

constexpr int maxn = 1e5+10;

std::pair<int,int> a[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &(a+i)->first, &(a+i)->second);
	long long ans = 0;
	std::sort(a+1, a+n+1);
	int longe = a[1].first + a[1].second;
	for(int i = 1; i <= n; i++) {
		ans += std::max(0, a[i].first - longe) + a[i].second;
		longe = std::max(longe, a[i].first + a[i].second);
	}
	printf("%lld\n", ans);
}
