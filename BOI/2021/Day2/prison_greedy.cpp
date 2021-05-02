#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e6+10;

vector<int> g[maxn];

int a[maxn], add[maxn], rmv[maxn], dp[maxn], ans;

vector<int> roots, b, st;

vector<int> bfs() {
	queue<int> q;
	vector<int> ord;
	for(int x : roots)
		q.push(x);
	
	while(q.size()) {
		int u = q.front(); q.pop();
		ord.push_back(u);
		for(int v : g[u])
			q.push(v);
	}

	reverse(ord.begin(), ord.end());

	return ord;
}

int main() {
	int n, d, t; scanf("%d %d %d", &n, &d, &t);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if(a[i] <= t) add[i] = min(n, i + t - a[i]), ++rmv[min(n, i + t - a[i]) + 1], ++ans;
	}
	
	for(int i = 1, atv = 0; i <= n; i++) {
		atv -= rmv[i];
		if(add[i]) {
			++atv;
			st.push_back(add[i] + n);
		}
		else {
			if(!atv) continue;
			++ans;
			while(st.size()) {
				if(st.back() > n && st.back()-n >= i) break;
				if(st.back() <= n) g[i].push_back(st.back());
				st.pop_back();
			}
			st.push_back(i);
		}
	}
	
	while(st.size()) {
		if(st.back() <= n) roots.push_back(st.back());
		st.pop_back();
	}

	vector<int> ord = bfs();
	for(int u : ord) {
		if(!g[u].size()) dp[u] = 1;
		else {
			vector<int> here;
			int mx = 0, ok = 0;
			for(int v : g[u])
				here.push_back(dp[v]), mx = max(mx, here.back());
			for(int x : here)
				if(x == mx && !ok) ok = 1;
				else b.push_back(x);
			dp[u] = mx+1;
		}
	}

	for(int x : roots)
		b.push_back(dp[x]);

	sort(b.begin(), b.end());
	while(d-- && b.size())
		ans -= b.back(), b.pop_back();
	printf("%d\n", ans);
}