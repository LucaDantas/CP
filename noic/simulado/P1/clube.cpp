#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e3 + 100;

vi g[maxn];

int dp[maxn];

int dfs(int u) {
	if(dp[u] != -1) return dp[u];
	dp[u] = 1;
	for(auto v : g[u]) {
		dp[u] = max(dp[u], dfs(v)+1);
	}
	return dp[u];
}

int main(){
	int n; scanf("%d", &n);
	vi a(n); read(a,0,n);
	sort(all(a), greater<int>());
	for(int i = 0; i < n; i++)
		for(int j = 0; j < i; j++)
			if(a[j]%a[i] == 0)
				g[j].pb(i); // It's actually inversed but it works anyway
	int ans = 0;
	clr(dp, -1);
	rep(i,0,n) ans = max(ans, dfs(i));
	printf("%d\n", ans);
}
