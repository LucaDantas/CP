// Gulosao brute pra subtask 1
#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e3+10, maxq = 1e6+10;

struct Pt
{
	int x, y, id;
	Pt(int _x, int _y, int _id = 0) : x(_x), y(_y), id(_id) {}
	Pt() {}
	Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
	long long operator/(Pt a) { return 1ll*x*a.y - 1ll*y*a.x; }
	long long operator*(Pt a) { return 1ll*x*a.x + 1ll*y*a.y; }
	bool operator<(Pt a) { return x == a.x ? y < a.y : x < a.x; }
} pts[maxn];

bool mark[maxn];

int juntar[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x, y, k; scanf("%d %d %d", &x, &y, &k);
		assert(k == 1);
		pts[i] = Pt(x, y, i);
		scanf("%d", &juntar[i]);
	}
	int q; scanf("%d", &q); assert(q <= 1000);
	while(q--) {
		int A, B; scanf("%d %d", &A, &B);
		Pt p(A, B);
		sort(pts, pts+n, [&](Pt a, Pt b) {
			return p*a > p*b;
		});
		long long ans = 0;
		for(int i = 0; i < n; i++)
			if(!mark[juntar[pts[i].id]])
				ans += p * pts[i], mark[juntar[pts[i].id]] = 1;
		memset(mark, 0, sizeof mark);
		printf("%lld\n", ans);
	}
}