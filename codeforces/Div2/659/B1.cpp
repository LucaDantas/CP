#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb emplace_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int n, k, l;
vector<vector<int>> dp;
vi d, p;

bool solve(int pos, int t, int here) {
	if(here == 2*k) return false;
	if(pos == n) return true;

	int level = d[pos] + p[t];
	if(level > l) return false;
	
	if(dp[pos][t] != -1) return dp[pos][t];

	int prox_temp = (t+1)%(2*k);
	return (dp[pos][t] = (solve(pos, prox_temp, here+1)
		|| solve(pos+1, prox_temp, 0)));
}

void TEST() {
	scanf("%d %d %d", &n, &k, &l);
	
	d.resize(n);
	rep(i,0,n) scanf("%d", &d[i]);

	p.resize(2*k);
	rep(i,0,k) p[i] = i;
	rep(i,k,2*k) p[i] = 2*k-i;

	dp = vector<vector<int>>(n+1, vi(2*k, -1));
	bool ans = 0;
	rep(i,0,2*k) ans = ans || solve(0, i, 0);
	puts(ans?"Yes":"No");
}

int main() {
	int T; scanf("%d", &T);
	while(T--) TEST();
}
