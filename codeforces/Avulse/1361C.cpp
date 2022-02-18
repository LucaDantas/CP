#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
#define pb push_back
using pii = pair<int,int>;

constexpr int maxn = 1<<21, logn = 20;

int val[maxn], n;
bool mark[maxn];

vector<pair<int,int>> g[maxn];

void dfs(int u) {
	mark[u] = 1;
	for(auto [v, id] : g[u])
		if(!mark[v]) dfs(v);
}

bool check(int mask) {
	for(int i = 0; i <= mask; i++) g[i].clear();

	for(int i = 0; i < n; i++) {
		int a = val[i<<1] & mask, b = val[i<<1|1] & mask;
		g[a].pb({b, i<<1});
		g[b].pb({a, i<<1|1});
	}

	int comp = 0;
	memset(mark, 0, sizeof mark);
	for(int i = 0; i <= mask; i++) {
		if(g[i].size() && !mark[i]) ++comp, dfs(i);
		if(g[i].size() & 1) { return 0; } // não da pra fazer um ciclo euleriano
	}
	
	return comp == 1; // não é conexo
}

vector<int> ans;

void go(int u, int p = -1) {
	while(g[u].size()) {
		auto [v, id] = g[u].back();
		g[u].pop_back();

		if(mark[id / 2]) continue;
		mark[id / 2] = 1;

		go(v, id);
	}

	if(p != -1) ans.pb(p^1), ans.pb(p);
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		val[i<<1] = a, val[i<<1|1] = b;
	}
	for(int l = logn; l >= 0; l--) {
		if(check((1<<l)-1)) {
			memset(mark, 0, sizeof mark);
			for(int i = 0; i < (1<<l); i++)
				if(g[i].size()) { go(i, -1); break; }

			printf("%d\n", l);
			for(int i = 0; i < n<<1; i++)
				printf("%d ", ans[i]+1);
			puts("");

			break;
		}
	}
}
