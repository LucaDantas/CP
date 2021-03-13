// Subtask only 1 convex hull + ternary search
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<cassert>

constexpr int maxn = 2e3+10;

struct Pt
{
	long long x, y;
	Pt(long long _x, long long _y) : x(_x), y(_y) {}
	Pt() {}
	Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
	long long operator/(Pt a) { return x*a.y - y*a.x; }
	long long operator*(Pt a) { return x*a.x + y*a.y; }
	bool operator<(Pt a) { return x == a.x ? y < a.y : x < a.x; }
	void db() { printf("db %lld %lld\n", x, y); }
} pts[maxn];

bool ccw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) > 0; }
bool cw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) < 0; }

std::map<std::pair<int,int>, int> mp;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x, y, k; scanf("%d %d %d", &x, &y, &k);
		pts[i] = Pt(x, y);
		for(int j = 0, trash; j < k; j++)
			scanf("%d", &trash);
	}
	std::sort(pts, pts+n);
	std::vector<Pt> hull;
	long long mx = 0;
	for(int i = 0; i < n; i++) {
		if(mp[{pts[i].x, pts[i].y}]++) continue;
		while(hull.size() >= 2 && !cw(hull[(int)hull.size()-2], hull.back(), pts[i]))
			hull.pop_back();
		hull.push_back(pts[i]); mx = std::max(mx, pts[i].y);
	}
	reverse(hull.begin(), hull.end());
	while(hull.back().y < mx) hull.pop_back();
	reverse(hull.begin(), hull.end());
	int q; scanf("%d", &q);
	while(q--) {
		int A, B; scanf("%d %d", &A, &B);
		Pt p(A, B);
		int l = 0, r = (int)(hull.size())-1;
		while(l < r) {
			int mid = (l+r) >> 1;
			if(p*hull[mid] > p*hull[mid+1]) r = mid;
			else l = mid+1;
		}
		printf("%lld\n", p*hull[l]);
	}
}