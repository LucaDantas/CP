#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>

constexpr int maxn = 210;

long long dp[maxn][maxn][2];
int pE[maxn], pR[maxn], tot;

std::vector<std::pair<int,int>> dir, esq;

void min_self(long long& a, long long b) { if(a > b) a = b; }

int main() {
	int n; scanf("%d", &n);
	
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		if(a < 0) esq.push_back({a, b});
		else dir.push_back({a, b});
		tot += b;
	}

	esq.push_back({0, 0}); dir.push_back({0, 0});
	std::sort(dir.begin(), dir.end());
	std::sort(esq.begin(), esq.end()); std::reverse(esq.begin(), esq.end());

	for(int i = 0; i < (int)(esq.size()); i++)
		pE[i] = (i ? pE[i-1] : 0) + esq[i].second;
	for(int i = 0; i < (int)(dir.size()); i++)
		pR[i] = (i ? pR[i-1] : 0) + dir[i].second;

	memset(dp, 0x3f, sizeof dp);
	dp[0][0][0] = 0;

	for(int i = 0; i < (int)(esq.size()); i++) {
		for(int j = 0; j < (int)(dir.size()); j++) {
			long long val = (tot - pE[i] - pR[j]);

			min_self(dp[i+1][j][0], dp[i][j][0] + val * (esq[i].first - esq[i+1].first));

			min_self(dp[i+1][j][0], dp[i][j][1] + val * (dir[j].first - esq[i+1].first));

			min_self(dp[i][j+1][1], dp[i][j][0] + val * (dir[j+1].first - esq[i].first));

			min_self(dp[i][j+1][1], dp[i][j][1] + val * (dir[j+1].first - dir[j].first));
		}
	}

	printf("%lld\n", std::min(dp[(int)(esq.size())-1][(int)(dir.size())-1][0], dp[(int)(esq.size())-1][(int)(dir.size())-1][1]));
}