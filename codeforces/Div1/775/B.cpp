#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

struct BIT {
	int n;
	vector<int> bit;
	void start(int _n) { n = _n; bit.assign(n+1, 0); }
	void upd(int x, int v) {
		for(; x <= n; x+=x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x-=x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, c; scanf("%d %d", &n, &c);
		vector<int> a(n);
		for(int& x : a)
			scanf("%d", &x);
		sort(a.begin(), a.end());
		a.erase(unique(a.begin(), a.end()), a.end());
		if(a.front() != 1) { puts("No"); continue; }
		vector<bool> mark(c+1);
		vector<int> pref(c+1);
		for(int x : a)
			mark[x] = 1;
		bool ans = 1;
		int menores = 0;
		bit.start(c);
		for(int x : a) {
			ans &= bit.query(x) == menores;
			// printf("%d %d\n", x, bit.query(x));
			for(int qtd = 0; qtd*x <= c; qtd++) {
				if(mark[qtd]) {
					bit.upd(qtd*x, 1);
					if((qtd+1)*x <= c)
						bit.upd(qtd*x+x, -1);
				}
			}
			++menores;
		}
		puts(ans ? "Yes" : "No");
	}
}
