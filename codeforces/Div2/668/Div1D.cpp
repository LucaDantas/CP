#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e6+10;

int cor[maxn], n, b, p;
vector<int> g[maxn];

void dfs(int u) {
	if(cor[u] == 1) b += u, b %= 2;
	else p += u, p %= 2;
	for(auto v : g[u]) {
		if(!cor[v]) {
			cor[v] = (cor[u]==1?2:1);
			dfs(v);
		}
	}
}

int inicial[maxn];

int main() {
	scanf("%d", &n);
	if(n&1) {
		puts("Second"); fflush(stdout);
		for(int i = 1; i <= 2*n; i++) {
			int p; scanf("%d", &p);
			if(!inicial[p]) inicial[p] = i;
			else g[inicial[p]].pb(i), g[i].pb(inicial[p]);
		}
		for(int i = 1; i <= n; i++) g[i].pb(i+n), g[i+n].pb(i);
		for(int i = 1; i <= 2*n; i++)
			if(!cor[i])
				cor[i] = 1, dfs(i);
				
		if(b == 0) for(int i = 1; i <= 2*n; i++) if(cor[i] == 1) printf("%d ", i);
		if(p == 0) for(int i = 1; i <= 2*n; i++) if(cor[i] == 2) printf("%d ", i);
	} else {
		puts("First"); fflush(stdout);
		for(int i = 0; i < 2*n; i++)
			printf("%d ", (i%n) + 1);
	}
	printf("\n");
}