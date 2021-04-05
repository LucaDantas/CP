#include <cstdio>
#include <set>

long long difl, difr; // lazy

std::multiset<long long> l, r;

long long ans = 0;

void sl(int i) {
	long long passar = *r.begin() + difr;
	r.erase(r.begin());
	ans += (passar - (*l.rbegin() + difl)) * (-i + (int)l.size());
	l.insert(passar - difl);
}

void sr(int i) {
	long long passar = *l.rbegin() + difl;
	l.erase(--l.end());
	ans -= (passar - (*l.rbegin() + difl)) * (-i + (int)l.size());
	r.insert(passar - difr);
}

long long abs(long long a) { return a < 0 ? -a : a; }

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) {
		long long a; scanf("%lld", &a);
		if(l.size()) ans += abs(a - *l.rbegin() - difl);
		if(!l.size() || a <= *l.rbegin() + difl) l.insert(a - difl), l.insert(a - difl);
		else r.insert(a - difr), r.insert(a - difr);
		while((int)l.size() > i) sr(i);
		while((int)r.size() > i) sl(i);
		difr += k;
		difl -= k;
	}
	printf("%lld\n", ans);
}