#include<cstdio>
#include<vector>
#include<utility>

std::vector<std::pair<int,int>> up, down;

long long ans = 0;

long long check(std::pair<int,int> a, std::pair<int,int> b) {
	return (long long)(a.second+b.second) * (a.first - b.first);
}

inline long long max(long long a, long long b) { return a > b ? a : b; }

void solve(int l, int r, int l2, int r2) {
	if(l > r) return;
	int m = (l+r) >> 1;
	int best = l2;
	for(int i = l2; i <= r2; i++)
		if(check(down[m], up[i]) > check(down[m], up[best]))
			best = i;
	ans = max(ans, check(down[m], up[best]));
	solve(l, m-1, l2, best);
	solve(m+1, r, best, r2);
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		if(!up.size() || x > up.back().second) up.push_back({i, x});
		while(down.size() && x > down.back().second) down.pop_back();
		down.push_back({i, x});
	}
	solve(0, (int)down.size()-1, 0, (int)up.size()-1);
	printf("%lld\n", ans);
}