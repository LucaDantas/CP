#include<cstdio>
#include<vector>
#include<utility>
using namespace std;

constexpr int maxn = 1e5+10;

struct DSU
{
	int pai[maxn], peso[maxn], color[maxn], bp = 1;
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	vector<pair<pair<int,int>,pair<int,int>>> sv;
	int find(int x, int& c) {
		while(pai[x] != x) {
			c ^= color[x];
			x = pai[x];
		}
		return pai[x];
	}
	void join(int a, int b) {
		int ca = 0, cb = 0;
		a = find(a, ca), b = find(b, cb);
		if(peso[a] < peso[b])
			swap(a, b), swap(ca, cb);
		sv.push_back({{a, b}, {bp, peso[a]}});
		if(a == b) return (void)(bp = (bp && ca!=cb));
		pai[b] = a;
		peso[a] += peso[b];
		color[b] = 1^ca^cb;
	}
	void rollback(int t) {
		while((int)sv.size() > t) {
			auto [pp, pp2] = sv.back();
			auto [a, b] = pp;
			auto [bip, p_a] = pp2;
			sv.pop_back();
			pai[b] = b;
			color[b] = 0;
			peso[a] = p_a;
			bp = bip;
		}
	}	
} dsu;

vector<pair<int,int>> edges;

int ans = 0;

void solve(int l, int r) {
	if(l == r) {
		auto [a, b] = edges[l];
		int ca = 0, cb = 0;
		if(dsu.find(a, ca) != dsu.find(b, cb) || ca == cb) ++ans;
		return;
	}
	int m = (l+r) >> 1;
	int t = (int)dsu.sv.size();
	for(int i = l; i <= m; i++) {
		dsu.join(edges[i].first, edges[i].second);
		if(!dsu.bp) break;
	}
	if(dsu.bp) solve(m+1, r);
	dsu.rollback(t);
	for(int i = m+1; i <= r; i++) {
		dsu.join(edges[i].first, edges[i].second);
		if(!dsu.bp) break;
	}
	if(dsu.bp) solve(l, m);
	dsu.rollback(t);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), edges.push_back({a, b});
	solve(0, m-1);
	printf("%d\n", ans);
}
