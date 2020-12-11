#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pli = pair<ll, int>;

#define ff first
#define ss second
#define pb push_back

constexpr int maxn = 1e5+10, mod = 1000000007, logn = 20;

ll gcd(ll a, ll b) {return !b?a:gcd(b,a%b);}

map<ll,int> GCD[2*maxn];

vector<int> g[maxn];

int n;

ll val[maxn], ans;

void dfs(int u, int p) {
	GCD[u][val[u]]++;
	for(auto it : GCD[u]) {
		ll next = gcd(it.ff, val[u]);
		ans = (ans + next % mod * it.ss) % mod;
		GCD[n+u][next] += it.ss; 
	}
	GCD[u] = GCD[n+u]; GCD[n+u].clear();
	for(int v : g[u]) {
		if(v == p) continue;
		GCD[v] = GCD[u];
		dfs(v, u);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &val[i]);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	dfs(1, 0);
	printf("%lld\n", ans);
}