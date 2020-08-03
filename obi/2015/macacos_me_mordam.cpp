#include<bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point
{
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() {}

	Point operator+(Point b) {
		return Point(x + b.x, y + b.y);
	}

	Point operator-(Point b) {
		return Point(x - b.x, y - b.y);
	}

	ll operator*(Point b) {
		return 1ll * x * b.y - 1ll * y * b.x;
	}
};

bool cw(Point a, Point b, Point c) { // c em relação à a->b
	b = b - a;
	c = c - a;
	return b * c >= 0;
}

const int maxn = 3e5+10;

Point pts[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x, y; scanf("%d %d", &x, &y);
		pts[i] = Point(x, y);
	}
	sort(pts+1, pts+n+1, [](const Point& a, const Point& b){
		return a.x < b.x;
	});
	vector<Point> hull;
	hull.push_back(pts[1]);
	for(int i = 2; i <= n; i++) {
		while(hull.size() >= 2 && cw(hull[hull.size()-2], hull.back(), pts[i]))
			hull.pop_back();
		hull.push_back(pts[i]);
	}
	printf("%d\n", (int)hull.size()-1);
}