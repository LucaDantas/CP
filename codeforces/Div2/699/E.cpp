#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) ((int)(a).size())

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 5e5 + 10;

vector<int> grp[maxn];

int a[maxn], dp[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		grp[a[i]].pb(i);
	}
	for(int i = 1; i <= n; i++) {
		dp[i] = dp[i-1]+1;
		if(grp[a[i]].back() == i)
			dp[i] = min(dp[i], dp[grp[a[i]].front()-1] + grp[a[i]].back()-grp[a[i]].front()+1 - sz(grp[a[i]]));
	}
	int ans = inf;
	for(int i = 1; i <= n; i++) {
		for(int j = sz(grp[i])-1; j >= 0; j--) {
			ans = min(ans, n-grp[i][j]+1 - (sz(grp[i]) - j) + dp[grp[i][j]-1]);
		}
	}
	printf("%d\n", ans);
}
