#include<cstdio>
#include<vector>
#include<utility>
using namespace std;

constexpr int maxn = 2e5+10;

struct DSU
{
	int pai[maxn], peso[maxn], color[maxn];
	bool bp = 1;
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	struct RollBack
	{
		int a, b, pa;
		bool bip;
	};
	vector<RollBack> sv;
	int find(int x, int& c) {
		while(pai[x] != x) {
			c ^= color[x];
			x = pai[x];
		}
		return x;
	}
	bool join(int a, int b) {
		int ca = 0, cb = 0;
		a = find(a, ca), b = find(b, cb);
		if(peso[a] < peso[b])
			swap(a, b), swap(ca, cb);
		sv.push_back({a, b, peso[a], bp});
		if(a == b) return bp = (bp && (ca!=cb));
		pai[b] = a;
		peso[a] += peso[b];
		color[b] = 1^ca^cb;
		return 1;
	}
	int sz() { return (int)sv.size(); }
	void rollback(int t) {
		while((int)sv.size() > t) {
			auto [a, b, pa, bip] = sv.back();
			sv.pop_back();
			pai[b] = b;
			peso[a] = pa;
			color[b] = 0;
			bp = bip;
		}
	}
} dsu;

int ans[maxn];
vector<pair<int,int>> edges;

void solve(int l, int r, int l2, int r2) {
	if(l > r) return;

	int m = (l+r) >> 1, t0 = dsu.sz();
	for(int i = l; i <= m; i++) {
		auto [a, b] = edges[i];
		dsu.join(a, b);
	}

	int t1 = dsu.sz(), m2 = -1;
	if(!dsu.bp) m2 = r2;
	else
		for(int i = r2; i >= max(m+1, l2); i--)
			if(!dsu.join(edges[i].first, edges[i].second))
				{m2 = i; break;}

	ans[m] = m2;

	dsu.rollback(t1);
	solve(m+1, r, m2, r2);
	dsu.rollback(t0);
	for(int i = r2; i > m2; i--)
		dsu.join(edges[i].first, edges[i].second);
	solve(l, m-1, l2, m2);
	dsu.rollback(t0);
}

int main() {
	int n, m, q; scanf("%d %d %d", &n, &m, &q);
	edges.push_back({0, maxn-1});
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), edges.push_back({a, b});
	edges.push_back({0, maxn-1});
	solve(0, m, 1, m+1);
	while(q--) {
		int a, b; scanf("%d %d", &a, &b);
		puts(ans[a-1] > b?"YES":"NO");
	}
}