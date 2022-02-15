#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 2e5+10, B = 320;

std::vector<std::pair<int,int>> g[maxn];

int depth[maxn], in[maxn], back[maxn], val[maxn], t;

bool vis[maxn];

void dfs(int u, int p) {
	depth[u] = depth[p]+1;
	in[u] = ++t;

	for(auto [v, x] : g[u]) if(v != p) {
		val[v] = x;
		back[t] = v;
		dfs(v, u), back[t] = v;
		++t;
	}
}

struct Query { int l, r, id; bool operator<(const Query& o) const { return l/B == o.l/B ? r < o.r : l < o.l; } } qr[maxn];

int freq[maxn], block[maxn], ans[maxn];

void add(int x, int add) { block[x/B] -= freq[x]>0; freq[x] += add; block[x/B] += freq[x]>0; }

int mex() {
	int id = 0;
	for(; block[id/B] == B; id += B);
	for(; freq[id]; id++);
	return id;
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1, a, b, x; i < n; i++)
		scanf("%d %d %d", &a, &b, &x), x = std::min(x, n+1), g[a].push_back({b, x}), g[b].push_back({a, x});
	dfs(1, 0);
	for(int qq = 0; qq < q; qq++) {
		int a, b; scanf("%d %d", &a, &b);
		if(in[a] > in[b]) std::swap(a, b);
		qr[qq] = {in[a], in[b], qq};
	}
	std::sort(qr, qr+q);
	
	int l = 1, r = 1;
	for(int i = 0; i < q; i++) {
		while(r < qr[i].r) {
			add(val[back[r]], (vis[back[r]] ? -1 : 1));
			vis[back[r]] ^= 1, ++r;
		}
		while(l < qr[i].l) {
			add(val[back[l]], (vis[back[l]] ? -1 : 1));
			vis[back[l]] ^= 1, ++l;
		}

		while(r > qr[i].r) {
			--r;
			add(val[back[r]], (vis[back[r]] ? -1 : 1));
			vis[back[r]] ^= 1;
		}
		while(l > qr[i].l) {
			--l;
			add(val[back[l]], (vis[back[l]] ? -1 : 1));
			vis[back[l]] ^= 1;
		}

		ans[qr[i].id] = mex();
	}

	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
