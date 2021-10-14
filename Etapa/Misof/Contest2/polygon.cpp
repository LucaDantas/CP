#include <bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())
#define pb push_back

constexpr int maxn = 1e5+10;

struct Pt
{
	int x, y;
	long long operator/(const Pt& p) {
		return 1ll * x * p.y - 1ll * y * p.x;
	}
	long long operator*(const Pt& p) {
		return 1ll * x * p.x + 1ll * y * p.y;
	}
	Pt operator-(const Pt& p) {
		return {x-p.x, y-p.y};
	}
	bool operator<(const Pt& p) const {
		if(x == p.x) return y < p.y;
		return x < p.x;
	}
};

bool ccw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) > 0; }
bool cw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) < 0; }

set<Pt> mark;

vector<Pt> get_upper(const vector<Pt>& pts) {
	int n = sz(pts);
	vector<Pt> hull;
	for(int i = 0; i < n; i++) {
		if(mark.count(pts[i])) continue;
		while(sz(hull) >= 2 && ccw(hull[sz(hull)-2], hull.back(), pts[i]))
			hull.pop_back();
		hull.pb(pts[i]);
	}
	return hull;
}

vector<Pt> get_lower(const vector<Pt>& pts) {
	int n = sz(pts);
	vector<Pt> hull;
	for(int i = 0; i < n; i++) {
		if(mark.count(pts[i])) continue;
		while(sz(hull) >= 2 && cw(hull[sz(hull)-2], hull.back(), pts[i]))
			hull.pop_back();
		hull.pb(pts[i]);
	}
	return hull;
}

long long area(Pt a, Pt b, Pt c) {
	return abs((b-a)/(c-a));
}

long long ans;

void compare(const vector<Pt>& outside, const vector<Pt>& inside) {
	for(int i = 0, ptr = 0; i < sz(outside)-1; i++) {
		while(ptr < sz(inside)-1 &&
			area(outside[i], outside[i+1], inside[ptr]) >= area(outside[i], outside[i+1], inside[ptr+1]))
			++ptr;
		ans = min(ans, area(outside[i], outside[i+1], inside[ptr]));
	}
}

long long get_area(const vector<Pt>& poly) {
	long long ans = 0;
	for(int i = 2; i < sz(poly); i++)
		ans += area(poly[0], poly[i-1], poly[i]);
	return abs(ans);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vector<Pt> pts(n);
		for(Pt& x : pts)
			scanf("%d %d", &x.x, &x.y);
		sort(all(pts));
		
		vector<Pt> upper, lower, upper_inside, lower_inside;

		upper = get_upper(pts);
		lower = get_lower(pts);

		for(const Pt& p : upper)
			mark.insert(p);
		for(const Pt& p : lower)
			mark.insert(p);

		upper_inside = get_upper(pts);
		lower_inside = get_lower(pts);

		mark.clear();

		if(!sz(upper_inside)) { puts("-1"); continue; }

		ans = 0x3f3f3f3f3f3f3f3f;
		compare(upper, upper_inside);
		compare(lower, lower_inside);

		printf("%lld\n", get_area(upper) + get_area(lower) - ans);
	}
}