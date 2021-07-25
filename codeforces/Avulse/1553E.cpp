#include <cstdio>
#include <vector>

constexpr int maxn = 3e5+10;

int p[maxn], cnt[maxn];

std::vector<int> ans;

bool mark[maxn];

void dfs(int u, int k, int n) {
	mark[u] = 1;
	if(!mark[(p[u]-1 + k) % n])
		dfs((p[u]-1 + k) % n, k, n);
}

void check(int k, int n, int m) {
	for(int i = 0; i < n; i++)
		mark[i] = 0;
	int inv = n;
	for(int i = 0; i < n; i++)
		if(!mark[i]) --inv, dfs(i, k, n);
	if(inv <= m) ans.push_back(k);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++)
			scanf("%d", &p[i]), cnt[i] = 0;
		for(int i = 0; i < n; i++) {
			if(p[i]-1 <= i) ++cnt[i - (p[i] - 1)];
			else ++cnt[i + n - (p[i] - 1)];
		}
		for(int i = 0; i < n; i++)
			if((n - cnt[i]) <= 2*m) check(i, n, m);
		
		printf("%ld", ans.size());
		for(int x : ans)
			printf(" %d", x);
		puts("");
		ans.clear();
	}
}
