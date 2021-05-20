#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back
#define all(a) (a.begin(), a.end())
#define sz(a) (int)(a.size())

const int maxn = 5e5+10;

int L, R, n;

vector<pii> g[maxn];

int depth[maxn];

void calc(int u, int p) {
	ll mx = 0;
	for(auto pp : g[u]) {
		auto [v, ind] = pp;
		if(v == p) continue;
		depth[v] = depth[u]+1;
		calc(v, u);
	}
}


int main() {
	scanf("%d %d %d", &n, &L, &R);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb({b, i}), g[b].pb({a, i});
	calc(1, 0);
	int mx = 0, longe = 1;
	for(int i = 1; i <= n; i++)
		if(depth[i] > mx) mx = depth[i], longe = i;
	calc(longe, 0);
	mx = 0;
	for(int i = 1; i <= n; i++)
		if(depth[i] > mx) mx = depth[i];
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans += depth[i] == mx;
	printf("%d\n", ans);
}