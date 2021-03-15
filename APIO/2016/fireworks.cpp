#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 3e5+10;

vector<int> g[maxn];
priority_queue<long long> changes[maxn];
int c[maxn], start_slope[maxn], n;
long long start_y[maxn];

void combine(int a, int b) {
	auto& q = changes[a];
	start_y[a] += start_y[b];
	start_slope[a] += start_slope[b];
	for(; changes[b].size(); changes[b].pop())
		q.push(changes[b].top());
}

void dfs(int u) {
	if(u >= n) {
		start_slope[u] = -1;
		start_y[u] = c[u];
		changes[u].push((long long)c[u]);
		changes[u].push((long long)c[u]);
	} else {
		int big = g[u][0];
		for(int v : g[u]) {
			dfs(v);
			if(changes[v].size() > changes[big].size())
				big = v;
		}
		swap(changes[u], changes[big]);
		start_slope[u] = start_slope[big];
		start_y[u] = start_y[big];
		for(int v : g[u])
			if(v != big) combine(u, v);
		auto& q = changes[u];
		while((int)q.size() > -start_slope[u] + 1)
			q.pop();
		if(!u) return;
		start_y[u] += (long long)c[u];
		assert(q.size() >= 2);
		long long a = q.top(); q.pop();
		long long b = q.top(); q.pop();
		q.push(a + c[u]);
		q.push(b + c[u]);
	}
}

int main() {
	int m; scanf("%d %d", &n, &m);
	for(int i = 1; i < n+m; i++) {
		int p; scanf("%d %d", &p, &c[i]);
		g[p-1].pb(i);
	}
	dfs(0);
	long long ans = start_y[0], last = 0;
	int slope = start_slope[0];
	auto& q = changes[0];
	vector<long long> opa;
	while(q.size())
		opa.pb(q.top()), q.pop();
	while(opa.size()) {
		ans += 1ll * slope * (opa.back() - last);
		last = opa.back(); opa.pop_back();
		++slope;
	}
	printf("%lld\n", ans);
}