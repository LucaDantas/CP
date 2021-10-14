#include <bits/stdc++.h>
using namespace std;

using ld = long double;

constexpr int maxn = 105, maxv = (maxn * 20);
constexpr ld eps = 1e-14;

ld p[maxv][maxv][2];

int main() {
	int n; scanf("%d", &n);
	p[0][0][0] = 1;
	for(int i = 0, val; i < n; i++) {
		scanf("%d", &val);
		for(int v = 0; v < maxv; v++) {
			for(int mx = v; mx < maxv; mx++) {
				if(p[v][mx][0] < eps) continue;
				// printf("%d %d -> %d %d %.5lf\n", i, val, v, mx, (double)p[v][mx][0]);
				// n me pegar
				p[v][mx][1] += (ld)0.5 * p[v][mx][0];
				// me pegar
				p[max(0, v + val)][max(mx, v+val)][1] += (ld)0.5 * p[v][mx][0];
			}
		}
		for(int v = 0; v < maxv; v++)
			for(int mx = v; mx < maxv; mx++)
				p[v][mx][0] = p[v][mx][1], p[v][mx][1] = 0;
	}
	ld ans = 0;
	for(int v = 0; v < maxv; v++)
		for(int mx = v; mx < maxv; mx++)
			ans += (ld)mx * p[v][mx][0];
	printf("%.10lf\n", (double)ans);
}
