#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

constexpr int maxn = 3e4+10;

struct Pt
{
	double x, y;
	Pt() {}
	Pt(double a, double b) : x(a), y(b) {}
	Pt operator*(double a) {return Pt(x*a, y*a);} // mult
	double operator*(Pt a) {return x*a.y-y*a.x;} // cross
	Pt operator-(Pt b) { return Pt(x-b.x, y-b.y);}
	Pt operator+(Pt b) { return Pt(x+b.x, y+b.y);}
	double val() {return x*y;}
	bool operator<(Pt a) {return x<a.x;}
};

bool cw(Pt a, Pt b, Pt c) {
	return (b-a)*(c-a) < 0;
}

int main() {
	int n, C; scanf("%d %d", &n, &C);
	vector<Pt> hull, a;
	for(int i = 0; i < n; i++) {
		int c; double x, y;
		scanf("%d %lf %lf", &c, &x, &y);
		a.push_back(Pt(x*(double)C/c, y*(double)C/c));
	}
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++) {
		while(hull.size() >= 2 && !cw(hull[hull.size()-2], hull.back(), a[i]))
			hull.pop_back();
		hull.push_back(a[i]);
	}
	Pt last(0, 0);
	double ans = 0;
	for(Pt k : hull) {
		double l = 0, r = 1;
		for(int cnt = 0; cnt < 120; cnt++) {
			double m = l + (r-l)/3.00;
			double p1 = (last*m+k*(1-m)).val();
			m = r - (r-l)/3.00;
			double p2 = (last*m+k*(1-m)).val();
			ans = max({ans, p1, p2});
			if(p1 < p2) l += (r-l)/3.00;
			else r -= (r-l)/3.00;
		}
		last = k;
	}
	printf("%.2lf\n", (double)ans);
}