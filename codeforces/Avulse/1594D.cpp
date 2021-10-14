#include <cstdio>
#include <vector>
#include <cstring>

constexpr int maxn = 1e6+10;

const char *eq = "crewmate";

int max(int a, int b) { return a > b ? a : b; }

int t;
std::vector<int> g[maxn];

void join_1(int a, int b) { ++t, g[a].push_back(t), g[t].push_back(a), g[b].push_back(t), g[t].push_back(b); }

void join_2(int a, int b) { g[a].push_back(b), g[b].push_back(a); }

int n;
bool ok, mark[maxn], cor[maxn];
int tot, atv;

void dfs(int u) {
	mark[u] = 1;
	if(u <= n) ++tot, atv += cor[u];
	for(int v : g[u]) if(!mark[v]) {
		cor[v] = !cor[u];
		dfs(v);
	} else ok &= cor[u] != cor[v];
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int m; scanf("%d %d", &n, &m);
		t = n;
		
		static char s[10];
		for(int i = 0, a, b; i < m; i++) {
			scanf("%d %d %s", &a, &b, s);
			if(strcmp(s, eq) == 0) join_1(a, b);
			else join_2(a, b);
		}
		
		int ans = 0;
		ok = 1;
		for(int i = 1; i <= t; i++) {
			if(!mark[i]) {
				tot = 0, atv = 0, dfs(i);
				ans += max(atv, tot - atv);
			}
		}

		printf("%d\n", ok ? ans : -1);
		
		for(int i = 1; i <= t; i++)
			g[i].clear(), cor[i] = 0, mark[i] = 0;
	}
}
