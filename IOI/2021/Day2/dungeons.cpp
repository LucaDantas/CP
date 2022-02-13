#include "dungeons.h"
#include <vector>

constexpr int maxn = 4e5+10, logn = 24, log_lift = 12, base_lift = 4;
constexpr int inf = 0x3f3f3f3f;

struct FunctionalGraph {
	int f[log_lift][maxn];
	int tab[log_lift][maxn];
	long long cost[log_lift][maxn];

	void add_i(const int& i, const int& x, const int& v, const int& st) { f[0][i] = x, cost[0][i] = v, tab[0][i] = st; }

	void build(int n) {
		f[0][n] = n;

		for(int l = 1; l < log_lift; l++) {
			for(int i = 0; i <= n; i++) {
				f[l][i] = i;
				tab[l][i] = tab[l-1][i];

				for(int k = 0; k < base_lift; k++) {
					if(tab[l-1][f[l][i]] < inf)
						tab[l][i] = std::max(0ll, std::min((long long)tab[l][i], tab[l-1][f[l][i]] - cost[l][i]));
					cost[l][i] += cost[l-1][f[l][i]];
					f[l][i] = f[l-1][f[l][i]];
				}
			}
		}
	}

	void go(int& x, long long& val) {
		for(int l = log_lift-1; l >= 0; l--)
			for(int k = 0; k < base_lift-1; k++)
				if(tab[l][x] >  val || tab[l][x] == inf) val += cost[l][x], x = f[l][x];
	}
} graph[logn];

void init(int n, std::vector<int> s, std::vector<int> p, std::vector<int> w, std::vector<int> l) {
	for(int lg = 0; lg < logn; lg++) {
		for(int i = 0; i < n; i++) {
			if(s[i] < (2<<lg)) graph[lg].add_i(i, w[i], s[i], inf);
			else graph[lg].add_i(i, l[i], p[i], s[i]);
		}
		graph[lg].build(n);
	}

	return;
}

long long simulate(int x, int z) {
	long long val = z;
	for(int lg = 0; lg < logn; lg++)
		graph[lg].go(x, val);
	return val;
}
