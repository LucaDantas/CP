#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

long long dist[maxn][maxn];

bool mark[maxn][maxn];

vector<pair<int,int>> g[maxn];

int n, m;

void dijkstra(int s) {
	for(int i = 0; i < maxn; i++)
		dist[s][i] = inf;
	dist[s][s] = 0;
	
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
	q.push({0, s});

	while(q.size()) {
		int u = q.top().second; q.pop();
		if(mark[s][u]) continue; mark[s][u] = 1;
		for(auto [v, w] : g[u])
			if(dist[s][v] > dist[s][u] + w)
				dist[s][v] = dist[s][u] + w, q.push({dist[s][v], v});
	}
}

void calc() { for(int i = 1; i <= n; i++) dijkstra(i); }

long long dp[maxn];
int k;
long long u[maxn],s[maxn],t[maxn];
bool ok(long long lim) {
	dp[0]  = 0;
	for(int i=1;i<=k;i++)dp[i] = inf;
	for(int i=1;i<=k;i++){

		long long cur = 0;
		cur = dist[1][u[i]];
		long long mn = s[i] - cur;
		for(int j=i;j<=k;j++){
			//cout << max(dp[i-1],t[j])<<" "<<lim + mn<<" "<<mn <<endl;
			if(max(dp[i-1],t[j]) <= lim + mn){
				long long tempo = max(dp[i-1],(long long)t[j]) + cur + dist[u[j]][1];
				dp[j] = min(dp[j],tempo);
			//	cout << j <<" "<<tempo << " "<<dp[j] << endl;
			}
			if(j!=k)
				cur += dist[u[j]][u[j+1]],mn = min(mn,s[j+1] - cur);
		}
	}

	return (dp[k]!=inf);
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0, a, b, w; i < m; i++)
		scanf("%d %d %d", &a, &b, &w), g[a].push_back({b, w}), g[b].push_back({a, w});
	calc();
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
		scanf("%lld%lld%lld",&s[i],&u[i],&t[i]);

	long long l = 0, r = inf, ans = -1;
	while(l <= r) {
		long long m = (l+r) >> 1;
		if(ok(m)) ans = m, r = m-1;
		else l = m+1;
	}
	printf("%lld\n", ans);
}
