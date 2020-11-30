#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define all(a) (a).begin(), (a).end()
#define pb push_back
#define ff first
#define ss second

constexpr int maxn = 1e5+10;

int ans[maxn];

vector<int> g[maxn];

struct Path
{
	set<pii> st;
	inline int find(int u) { return (*st.upper_bound({u, 0})).ss; }
	void add(int v, int t) {
		auto it = st.lower_bound({v, 0});
		if((*it).ss >= t) return;
		if((*it).ff == v) st.erase(it);
		st.insert({v, t});
		it = st.find({v, t});
		if(it == st.begin()) return;
		vector<pii> rm;
		for(--it;; --it) {
			if((*it).ss <= t)
				rm.pb(*it);
			else break;
			if(it == st.begin()) break;
		}
		for(pii x : rm)
			st.erase(x);
	}
} go[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, a, b; i < m; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	for(int i = 1; i <= n; i++)
		ans[i] = 1, go[i].st.insert({maxn, 1});
	for(int u = n; u >= 1; u--) {
		sort(all(g[u])); reverse(all(g[u]));
		int mx = 0;
		for(int v : g[u]) {
			int nice = go[v].find(u);
			go[v].add(u, 2+mx);
			mx = max(mx, nice);
		}
		ans[u] = max(ans[u], mx+1);
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}