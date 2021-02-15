#include<cstdio>
#include<vector>
#include<utility>
#include<algorithm>
#include<cassert>
#include<map>
using namespace std;

constexpr int maxn = 1e5+10;

vector<int> g[maxn], grp[maxn], grp_lvl[maxn];
int a[maxn], cor[maxn], leaf[maxn], mx;
pair<int,pair<int,int>> dp[maxn];

void dfs(int u, int d) {
	mx = max(mx, d);
	++a[d];
	grp[d].push_back(u);
	leaf[u] = 1;
	for(int v : g[u])
		leaf[u] = 0, dfs(v, d+1);
}

int main() {
	int n, x, sv_x; scanf("%d %d", &n, &x), sv_x = x;
	for(int i = 2, p; i <= n; i++)
		scanf("%d", &p), g[p].push_back(i);
	dfs(1, 0);

	map<int,int> mp;
	for(int i = 0; i <= mx; i++)
		++mp[a[i]], grp_lvl[a[i]].push_back(i);

	vector<pair<int,int>> freq;
	for(auto it : mp)
		freq.push_back({it.first, it.second});

	dp[0].first = 1;
	
	for(auto pp : freq) {
		auto [val, f] = pp;
		for(int inicio = 0; inicio < val; inicio++) {
			int last = -maxn;
			for(int i = inicio; i <= x; i += val) {
				if(dp[i].first) last = i;
				else if(last >= i-val*f) dp[i] = {1, {val, (i-last)/val}};
			}
		}
	}

	if(dp[x].first) {
		printf("%d\n", mx+1);
		while(x) {
			auto [val, qtd] = dp[x].second;
			for(int i = 0; i < qtd; i++)
				for(int x : grp[grp_lvl[val][i]])
					cor[x] = 1;
			x -= val*qtd;
		}
	} else {
		printf("%d\n", mx+2);
		int m = n;
		x = sv_x;
		for(int i = 0; i <= mx; i++) {
			if(a[i] <= x) for(int u : grp[i]) cor[u] = 1, --x;
			else if(a[i] > m-x) {
				if(x >= m-x)
					for(int u : grp[i])
						if(!leaf[u]) cor[u] = 1, --x;
				for(int u : grp[i])
					if(leaf[u])
						cor[u] = (--x)>=0?1:0;
				break;
			}
			m -= a[i];
		}
	}
	for(int i = 1; i <= n; i++)
		putchar(cor[i]?'a':'b');
	printf("\n");
}