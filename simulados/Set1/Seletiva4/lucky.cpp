#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10, inf = 0x3f3f3f3f;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(peso[a] < peso[b]) swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
	}
} dsu;

int cnt[maxn], dp[maxn];

struct MinQueue
{
	int t, t_rmv;
	MinQueue() : t(0), t_rmv(0) { q.clear(); }
	deque<pair<int,int>> q;
	void push(int v) {
		while(q.size() && v < q.front().first)
			q.pop_front();
		q.push_front({v, ++t});
	}
	void pop() { if(++t_rmv == q.back().second) q.pop_back(); }
	int query() { return q.size()?q.back().first:inf; }
};

bool good(int x) {
	while(x) {
		if(x%10 != 4 && x%10 != 7) return 0;
		x /= 10;
	}
	return 1;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), dsu.join(a-1, b-1);
	for(int i = 0; i < n; i++)
		if(dsu.find(i) == i) ++cnt[dsu.peso[i]];
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for(int peso = 1; peso <= n; peso++) {
		if(!cnt[peso]) continue;
		int qtd = cnt[peso];
		for(int st = 0; st < peso; st++) {
			MinQueue q;
			for(int i = st, shift = 0; i <= n; i += peso, ++shift) {
				q.push(dp[i] - shift);
				dp[i] = min(dp[i], q.query() + shift);
				if(shift >= qtd) q.pop();
			}
		}
	}
	int ans = inf;
	for(int i = 1; i <= n; i++)
		if(good(i)) ans = min(ans, dp[i]);
	printf("%d\n", ans<inf/2?ans-1:-1);
}