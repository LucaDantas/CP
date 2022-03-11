#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

struct DSU {
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return 1;
	}
} dsu;

vector<pair<int,int>> pts;

long long sq(int x) { return 1ll * x * x; }
long long dist(pair<int,int> a, pair<int,int> b) { return sq(a.first-b.first) + sq(a.second-b.second); }

struct Edge { long long val; int l, r; bool operator<(const Edge& o) { return val < o.val; } } edges[100*maxn];
int cnt = 0;

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x, y; scanf("%d %d", &x, &y);
		pts.push_back({x, y});
	}
	sort(pts.begin(), pts.end());
	for(int i = 0; i < n-1; i++)
		for(int j = 1; j < 100 && i+j < n; j++)
			edges[cnt] = {dist(pts[i], pts[i+j]), i, i+j}, ++cnt;

	sort(edges, edges+cnt);

	long long ans = 0;
	for(int i = 0; i < cnt; i++)
		if(dsu.join(edges[i].l, edges[i].r))
			ans += edges[i].val;

	printf("%lld\n", ans);
}
