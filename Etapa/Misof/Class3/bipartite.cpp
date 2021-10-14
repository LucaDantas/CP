#include <cstdio>
#include <vector>

constexpr int maxn = 1e5+10;

std::vector<int> g[maxn];

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int cor[maxn];
struct Edge {
	int a, b;
};
std::vector<Edge> ans;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[max(a, b)].push_back(min(a, b));
	for(int i = 1; i <= n; i++){
		static std::vector<int> l, r; l.clear(), r.clear();
		for(int v : g[i]) {
			// printf("%d = %d\n", i, v);
			if(cor[v]) l.push_back(v);
			else r.push_back(v);
		}
		cor[i] = 1;
		if(l.size() > r.size()) std::swap(l, r), cor[i] = 0;
		for(int e : l) ans.push_back({i, e});
		// printf("%d %d -> %ld %ld\n", i, cor[i], l.size(), r.size());
	}
	printf("%ld\n", ans.size());
	for(Edge e : ans)
		printf("%d %d\n", e.a, e.b);
}
