#pragma GCC optimize("Ofast") 
#pragma GCC optimize("no-stack-protector") 
#pragma GCC optimize("unroll-loops") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 30010;

struct Pt {
	int x, y;
	Pt(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	long long operator/(const Pt& o) const { return 1ll * x * o.y - 1ll * y * o.x; }
	Pt operator-(const Pt& o) const { return Pt(x-o.x, y-o.y); }
	int qd() const { return y == 0 ? x < 0 : y < 0; }

	friend bool cw(const Pt& a, const Pt& b, const Pt& c) { return (b-a)/(c-a) < 0; }
	friend bool ccw(const Pt& a, const Pt& b, const Pt& c) { return (b-a)/(c-a) > 0; }

	bool operator<(const Pt& o) const {
		if(qd() != o.qd()) return qd() < o.qd();
		return cw(Pt(0, 0), *this, o);
	}
} pt[maxn];

/* bool cw(const Pt& a, const Pt& b, const Pt& c) { return (b-a)/(c-a) < 0; }
bool ccw(const Pt& a, const Pt& b, const Pt& c) { return (b-a)/(c-a) > 0; } */

vector<Pt> tribe[maxn], ord[maxn][2];

Pt v[2];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int a, b, t; scanf("%d %d %d", &a, &b, &t);
		tribe[t].push_back(Pt(a, b));
	}
	
	for(int i = 0; i < 2; i++) {
		int a, b; scanf("%d %d", &a, &b);
		v[i] = Pt(a, b);
		for(int t = 1; i <= m; i++) {
			for(Pt p : tribe[t])
				ord[t][i].push_back(p-v[i]);
			sort(ord[t][i].begin(), ord[t][i].end());
		}
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)

	return 0;

	int q; scanf("%d", &q);
	while(q--) {
		int a, b; scanf("%d %d", &a, &b);
		int ans = 0;
		for(Pt p1 : tribe[a]) {
			if(ccw(p1, v[0], v[1])) {
				// tenho q inverter as coisas
			} else {
				// jeito normal
				ans += bs_last_cw(p1, v[0], ord[b][0]) - 

			}
			/* if(ccw(p1, v[0], v[1]))
				swap(v[0], v[1]);
			for(Pt p2 : tribe[b])
				ans += cw(p1, v[0], p2) && ccw(p1, v[1], p2); */
		}
		printf("%d\n", ans);
	}
}
