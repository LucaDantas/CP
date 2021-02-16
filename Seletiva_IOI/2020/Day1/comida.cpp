#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

struct Pt
{
	int x, y;
	Pt(int _x, int _y) : x(_x), y(_y) {}
	Pt() {}
	bool operator<(Pt a) {return x<a.x;}
	Pt operator-(Pt a) {return Pt(x-a.x, y-a.y);}
	long long operator/(Pt a) {return 1ll*x*a.y - 1ll*y*a.x;}
};

struct Frac
{
	int a, b; // a / b
	Frac(int _a, int _b) : a(_a), b(_b) {}
	bool operator<(Frac F) {return 1ll*a*F.b < 1ll*F.a*b;}
	bool operator>(Frac F) {return 1ll*a*F.b > 1ll*F.a*b;}
};

bool cw(Pt a, Pt b, Pt c) {
	return (b-a)/(c-a) < 0;
}

auto cmp = [](const pair<Frac, int>& a, const pair<Frac, int>& b) {
	Frac F1 = a.first, F2 = b.first;
	return F1 < F2;
};

priority_queue<pair<Frac, int>, vector<pair<Frac, int>>, decltype(cmp)> q(cmp);

vector<Frac> slopes[maxn];

int main() {
	int n; long long r, ans = 0; scanf("%d %lld", &n, &r);
	for(int i = 0; i < n; i++) {
		vector<Pt> pts, hull;
		int k; scanf("%d", &k); if(!k) continue;
		map<int,int> mp;
		while(k--) {
			int p, s; scanf("%d %d", &p, &s);
			mp[p] = max(mp[p], s);
		}
		for(auto it : mp)
			pts.push_back(Pt(it.first, it.second));
		for(Pt p : pts) {
			while(hull.size() >= 2 && !cw(hull[(int)hull.size()-2], hull.back(), p))
				hull.pop_back();
			if(!hull.size() || p.y > hull.back().y)
				hull.push_back(p);
		}
		ans += hull.front().y;
		r -= hull.front().x;
		for(int j = 1; j < (int)hull.size(); j++)
			slopes[i].push_back(Frac(hull[j].y-hull[j-1].y, hull[j].x - hull[j-1].x));
		reverse(slopes[i].begin(), slopes[i].end());
		if(slopes[i].size())
			q.push({slopes[i].back(), i}), slopes[i].pop_back();
	}
	if(r < 0) return puts("-1"), 0;
	while(q.size() && r > 0) {
		Frac val = q.top().first;
		int i = q.top().second;
		q.pop();
		ans += (1ll*min(r, 1ll*val.b)*val.a) / val.b;
		r -= val.b;
		if(slopes[i].size())
			q.push({slopes[i].back(), i}), slopes[i].pop_back();
	}
	printf("%lld\n", ans);
}