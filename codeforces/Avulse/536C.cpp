#include<cstdio>
#include<algorithm>
#include<vector>
 
constexpr int maxn = 2e5+10;
 
using I = __int128;
 
struct Frac
{
	I a, b;
	Frac(I _b) : a(1), b(_b) {}
	Frac(I _a, I _b) : a(_a), b(_b) {}
	Frac() : a(0), b(1) {}
	Frac operator-(Frac F) {
		return Frac(a*F.b-F.a*b, b*F.b);
	}
	Frac operator*(Frac F) {
		return Frac(a*F.a, b*F.b);
	}
	bool operator>(Frac F) {
		return a*F.b > F.a*b;
	}
	bool operator<(Frac F) {
		return a*F.b < F.a*b;
	}
	bool operator<=(Frac F) {
		return a*F.b <= F.a*b;
	}
	bool operator==(Frac F) {
		return a*F.b == F.a*b;
	}
};
 
struct Pt
{
	Frac x, y; std::vector<int> id;
	Pt(Frac _x, Frac _y, int _id) : x(_x), y(_y), id(std::vector<int>(1, _id)) {}
	Pt(Frac _x, Frac _y) : x(_x), y(_y), id(std::vector<int>(0)) {}
	Pt() {}
	Pt operator-(Pt a) {
		return Pt(x - a.x, y - a.y);
	}
	Frac operator/(Pt a) {
		return x*a.y - y*a.x;
	}
	bool operator<(Pt a) {
		if(x == a.x) return y < a.y;
		return x < a.x;
	}
	bool operator==(Pt a) {
		return x==a.x && y == a.y;
	}
} pts[maxn];
 
bool cw(Pt a, Pt b, Pt c) {
	return (b-a)/(c-a) < Frac();
}
 
int main() {
	int n; scanf("%d", &n);
	for(int i = 1, x, y; i <= n; i++)
		scanf("%d %d", &x, &y), pts[i] = Pt(Frac(x), Frac(y), i);
	std::sort(pts+1, pts+n+1);
	std::vector<Pt> hull;
	for(int i = 1; i <= n; i++) {
	    if(hull.size() && pts[i] == hull.back()) { hull.back().id.push_back(pts[i].id[0]); continue; }
		while(hull.size() >= 2 && cw(hull[(int)hull.size()-2], hull.back(), pts[i]))
			hull.pop_back();
		if(!hull.size() || pts[i].y < hull.back().y)
		    hull.push_back(pts[i]);
	}
	std::vector<int> ans;
	for(Pt p : hull)
	    for(int x : p.id)
	        ans.push_back(x);
	std::sort(ans.begin(), ans.end());
	for(int id : ans)
		printf("%d ", id);
	printf("\n");
}
