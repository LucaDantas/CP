#include<cstdio>
#include<vector>

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

inline long long max(long long a, long long b) { return a > b ? a : b; }
inline long long min(long long a, long long b) { return a < b ? a : b; }

int main() {
	int n; long long d; scanf("%d %lld", &n, &d);
	long long mn = inf, mx = -inf;
	std::vector<long long> a;
	for(int i = 0; i < n; i++) {
		long long pos; scanf("%lld", &pos);
		a.push_back(pos);
		pos -= d*i;
		mn = min(pos, mn); mx = max(pos, mx);
	}
	long long ans = mx - mn;
	mn = inf, mx = -inf;
	for(int i = 0; i < n; i++) {
		long long pos = a[i];
		pos += d*i;
		mn = min(pos, mn); mx = max(pos, mx);
	}
	ans = min(ans, mx - mn);
	if(ans&1) printf("%lld.5\n", ans>>1);
	else printf("%lld.0\n", ans>>1);
}