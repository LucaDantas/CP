#include <cstdio>
#include <vector>

constexpr int maxn = 2e5+10;

std::vector<int> g[maxn], grp[2];

int cor[maxn], ans[maxn], qtd[2];
bool foi[maxn];

void dfs(int u, int p = 0) {
	++qtd[cor[u]];
	grp[cor[u]].push_back(u);
	for(int v : g[u]) if(v != p)
		cor[v] = cor[u]^1, dfs(v, u);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);

		dfs(1, 0);

		int c = qtd[1] <= qtd[0], q = qtd[c];

		for(int i = 0; i < 20; i++) {
			if(q & (1 << i)) {
				q ^= 1 << i;
				for(int j = (1 << i); j < (1 << (i+1)); j++) {
					ans[grp[c].back()] = j;
					grp[c].pop_back();
					foi[j] = 1;
				}
			}
		}

		for(int i = 1; i <= n; i++) {
			if(!foi[i]) {
				ans[grp[!c].back()] = i;
				grp[!c].pop_back();
			}
		}

		for(int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		puts("");

		for(int i = 1; i <= n; i++)
			ans[i] = 0, cor[i] = 0, foi[i] = 0, g[i].clear();
		for(int i : {0, 1})
			grp[i].clear(), qtd[i] = 0;
	}
}
