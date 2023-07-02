#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1<<18;

int dp[maxn];

struct Seg {
	struct Node {
		int add;
		int v;
	} tree[maxn<<1];
	void upd(int node, int i, int j, int l, int r, int val) {
		if(i > r || j < l) return;
		if(l <= i && j <= r) return (void)(tree[node].add += val, tree[node].v += val);
		int m = (i+j)>>1;
		upd(node<<1, i, m, l, r, val);
		upd(node<<1|1, m+1, j, l, r, val);
		tree[node].v = max(tree[node<<1].v, tree[node<<1|1].v) + tree[node].add;
	}
	int query() { return tree[1].v; }
} seg;

vector<pair<int,int>> itv[maxn]; // pra cada final salva o inicio e o custo

int main() {
	int n, k, A; scanf("%d %d %d", &n, &k, &A);
	int pre = 0;
	for(int i = 0; i < n; i++) {
		int l, r, c; scanf("%d %d %d", &l, &r, &c);
		r = k-r;
		itv[r].push_back({l, c});
		pre += c;
	}
	for(int x = 1; x <= k; x++) {
		dp[x] = dp[x-1];
		for(auto [l, c] : itv[x])
			seg.upd(1, 0, k, 0, l, c);
		seg.upd(1, 0, k, 0, x-1, -A);
		dp[x] = max(dp[x], seg.query());
		seg.upd(1, 0, k, x, x, dp[x]);
	}
	printf("%d\n", pre - dp[k]);
}
