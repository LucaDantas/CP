#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

constexpr int maxn = 1e6+10;

std::vector<int> pos[maxn];

int a[maxn], dp[maxn], pai[maxn], removi[maxn];

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]), pos[a[i]].push_back(i);
	memset(dp, 0x3f, sizeof dp);
	for(int i = 1; i <= k; i++) {
		for(int j = 0; j < (int)pos[i].size(); j++) {
			int eu = pos[i][j];
			int id = std::lower_bound(pos[i-1].begin(), pos[i-1].end(), eu) - pos[i-1].begin() - 1;
			if(j == 0) dp[eu] = 0;
			int ant = j>0?pos[i][j-1]:eu;
			if(!pos[i-1].size() || id < 0) {
				dp[eu] = (i==1) * (j+1);
				pai[eu] = i==1 ? ant : eu;
				removi[eu] = i==1;
			}
			else {
				// dp[eu] = std::min(dp[ant]+1, dp[pos[i-1][id]]);
				if(dp[ant]+1 < dp[pos[i-1][id]])
					pai[eu] = ant, removi[eu] = 1, dp[eu] = dp[ant]+1;
				else pai[eu] = pos[i-1][id], dp[eu] = dp[pos[i-1][id]];
			}
		}
	}
	if(!pos[k].size()) return puts("0"), 0;
	printf("%d\n", dp[pos[k].back()]);
	int id = pos[k].back();
	while(1) {
		if(removi[id]) printf("%d ", id+1);
		if(pai[id] == id) break;
		id = pai[id];
	}
	printf("\n");
}