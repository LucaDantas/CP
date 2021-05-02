#include <cstdio>
#include <algorithm>
#include <map>

constexpr int maxn = 25, maxv = 531441;

struct Event
{
	long long x, y; int t;
	bool operator<(const Event& o) const { if(x != o.x) return x < o.x; return t < o.t; }
} ev[2*maxv];

int a[maxn], pot[13];

std::map<long long,long long> mp;

void upd(long long x, long long v) { 
	auto it = mp.upper_bound(x);
	if(it != mp.begin() && prev(it)->second >= v) return;
	mp[x] = v;
	it = mp.find(x);
	while(next(it) != mp.end() && next(it)->second <= v)
		mp.erase(next(it));
}

long long query(long long x) {
	auto it = mp.upper_bound(x);
	if(it == mp.begin()) return -0x3f3f3f3f3f3f3f3f;
	return prev(it)->second;
}

int main() {
	pot[0] = 1;
	for(int i = 1; i <= 12; i++)
		pot[i] = pot[i-1] * 3;
	int n; scanf("%d", &n);
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for(int i = 0; i < n; i++)
		scanf("%d", a+i);
	int b = (n+1) >> 1, ptr = 0;
	for(int i = 0; i < pot[b]; i++) {
		int v = i;
		long long grp[3]{};
		for(int j = 0; j < b; j++) {
			grp[v % 3] += a[j];
			v /= 3;
		}
		ev[ptr++] = {grp[0] - grp[1], grp[1] - grp[2], 1};
	}
	b = n >> 1;
	for(int i = 0; i < pot[b]; i++) {
		int v = i;
		long long grp[3]{};
		for(int j = 0; j < b; j++) {
			grp[v % 3] += a[j + ((n+1) >> 1)];
			v /= 3;
		}
		ev[ptr++] = {-(grp[0] - grp[1]), -(grp[1] - grp[2]), 0};
	}
	std::sort(ev, ev+ptr);
	for(int i = 0; i < ptr; i++) {
		auto [x, y, t] = ev[i];
		if(t) ans = std::min(ans, x + y - query(y));
		else upd(y, x + y);
	}
	printf("%lld\n", ans);
}