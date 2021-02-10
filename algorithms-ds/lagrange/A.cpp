#include<cstdio>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;

using pli = pair<long long, int>;

#define pb push_back

constexpr int maxn = 3e5+10;
constexpr long long inf = 0x3f3f3f3f3f3f;

inline void max_self(long long& a, long long b) { a = max(a, b); }

long long dp[maxn][2], lambda;

int cnt[maxn][2];

vector<pair<int,int>> g[maxn];

pli comp(pli a, pli b) {
	if(a.first != b.first) return max(a, b);
	return a.second<b.second?a:b;
}

void dfs(int u, int p) {
	for(auto pp : g[u]) {
		auto [v, w] = pp;
		if(v == p) continue;
		dfs(v, u);
		auto [x, y] = comp({dp[u][1] + dp[v][1], cnt[u][1] + cnt[v][1]},
		{dp[u][0] + dp[v][0] + 1ll*w - lambda, cnt[u][0] + cnt[v][0] + 1});
		dp[u][1] = x; cnt[u][1] = y;

		dp[u][0] += dp[v][1];
		cnt[u][0] += cnt[v][1];
	}
	auto [x, y] = comp({dp[u][1], cnt[u][1]}, {dp[u][0], cnt[u][0]});
	dp[u][1] = x; cnt[u][1] = y;
}

int main() {
	int n, K; scanf("%d %d", &n, &K);
	for(int i = 1, a, b, c; i < n; i++)
		scanf("%d %d %d", &a, &b, &c), g[a].pb({b, c}), g[b].pb({a, c});
	long long l = -inf, r = inf, ans = 0;
	while(l <= r) {
		lambda = (l+r) >> 1;
		dfs(1, 0);
		if(cnt[1][1] <= K)
			ans = lambda, r = lambda-1;
		else l = lambda+1;
		memset(dp, 0, sizeof dp);
		memset(cnt, 0, sizeof cnt);
	}
	lambda = ans;
	dfs(1, 0);
	if(dp[1][1] + lambda*K < -inf/2)
		return puts("Impossible"), 0;
	printf("%lld\n", dp[1][1] + lambda*K);
}