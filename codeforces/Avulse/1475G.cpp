#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+1;

int f[maxn];

vector<int> pr;

void calc() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i])
			f[i] = i, pr.pb(i);
		for(int j = 0; j < (int)pr.size() && pr[j]*i < maxn && pr[j] <= f[i]; j++)
			f[pr[j] * i] = pr[j];
	}
}

int main() {
	calc();
	int t; scanf("%d", &t);
	while(t--) {
		int n, ans = 0; scanf("%d", &n);
		vector<int> a(maxn), dp(maxn);
		for(int i = 0; i < n; i++) {
			int x; scanf("%d", &x);
			++a[x];
		}
		for(int i = 1; i < maxn; i++) {
			int x = i;
			while(x > 1) {
				dp[i] = max(dp[i], dp[i/f[x]]);
				x /= f[x];
			}
			dp[i] += a[i];
			ans = max(ans, dp[i]);
		}
		printf("%d\n", n-ans);
	}
}