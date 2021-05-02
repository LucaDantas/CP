#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+10;

mt19937 rng(random_device{}());

struct Pt
{
	int x, y;
	Pt(int a = 0, int b = 0) : x(a), y(b) {}
	long long operator%(const Pt& p) const { return 1ll * x * p.y - 1ll * y * p.x; }
	Pt operator-(Pt p) { return Pt(x-p.x, y-p.y); }
	bool operator==(Pt p) const { return x == p.x && y == p.y; }
};

bool half(Pt p) { return p.y < 0 || (p.y == 0 && p.x < 0); }

bool operator<(const Pt& a, const Pt& b) {
	if(half(a) != half(b)) return half(a) < half(b);
	return a%b > 0;
}

Pt trees[maxn], camps[maxn];

bool vivo[maxn];

vector<pair<Pt, int>> pts;

int main() {
	int W, H;
	scanf("%d %d", &W, &H);
	int sx, sy; scanf("%d %d", &sx, &sy);
	int c; scanf("%d", &c);
	for(int i = 0, x, y; i < c; i++)
		scanf("%d %d", &x, &y), camps[i] = Pt(x, y), vivo[i] = 1;
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x, y; scanf("%d %d", &x, &y);
		trees[i] = Pt(x, y);
	}
	
	// Dou um shuffle pra n ficar com muita gente viva toda hora
	shuffle(trees, trees+n, rng);

	for(int i = 0; i < n; i++) {
		pts.clear();
		pts = {{Pt(sx, sy) - trees[i], 1}};
		
		for(int j = 0; j < n; j++)
			if(i != j) pts.push_back({trees[i] - trees[j], 0});

		for(int j = 0; j < c; j++)
			if(vivo[j]) vivo[j] = 0, pts.push_back({camps[j] - trees[i], 2+j});

		sort(pts.begin(), pts.end());

		int pos = -1, sz = (int)pts.size();
		for(int j = 0; j < sz; j++)
			if(pts[j].second == 1) { pos = j; break; }

		for(int j = (pos+1)%sz; pts[j].second; j = (j+1)%sz)
			vivo[pts[j].second-2] = 1;

		for(int j = (pos+sz-1)%sz; pts[j].second; j = (j+sz-1)%sz)
			vivo[pts[j].second-2] = 1;
	}

	vector<int> ans;
	for(int i = 0; i < c; i++)
		if(vivo[i]) ans.push_back(i+1);
	printf("%ld\n", ans.size());
	for(int x : ans)
		printf("%d ", x);
	printf("\n");
}