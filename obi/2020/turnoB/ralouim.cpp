#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define ff first
#define ss second

#define pb push_back

#define all(a) a.begin(), a.end()

constexpr int maxn = 2e3+10;
constexpr int inf = 0x3f3f3f3f;

struct Edge
{
	int a, b, w;
};

struct Pt
{
	int x, y, id;
};

vector<Edge> edges;

inline int sq(int x) {return x*x;}

int Dist(Pt a, Pt b) {
	return sq(a.x - b.x) + sq(a.y - b.y);
}

int ans[maxn][2], last[maxn][2], cnt;

int main() {
	int n; scanf("%d", &n);
	vector<Pt> pt(n+1);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &pt[i].x, &pt[i].y), pt[i].id = ++cnt;
	last[0][0] = last[0][1] = inf;
	for(int i = 1; i <= n; i++) {
		last[i][0] = last[i][1] = inf;
		ans[i][0] = ans[i][1] = -inf;
	}
	for(auto a : pt) {
		for(auto b : pt) {
			if(a.id == b.id || !b.id) continue;
			edges.pb({a.id, b.id, Dist(a, b)});
		}
	}
	sort(all(edges), [](const Edge& a, const Edge& b){
		return a.w > b.w;
	});
	for(auto e : edges) {
		if(last[e.a][0] == e.w && ans[e.a][1] >= ans[e.b][0])
		{
			ans[e.b][0] = ans[e.a][1]+1; last[e.b][0] = e.w;
		}
		else if(last[e.a][0] != e.w && ans[e.a][0] >= ans[e.b][0])
		{
			ans[e.b][1] = ans[e.b][0]; last[e.b][1] = last[e.b][0];
			ans[e.b][0] = ans[e.a][0]+1; last[e.b][0] = e.w;
		}
	}
	int bom = 0;
	for(int i = 0; i < n; i++)
		bom = max(bom, ans[i][0]);
	printf("%d\n", bom);
}