#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())

constexpr int maxn = 300+10, mod = 1 << 30;

vector<int> a[maxn];

long long ans = 0;

void add(ll& a, long long x) {
	x %= mod;
	a += (int)x;
	a %= mod;
}

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

vector<pair<int,int>> todos;

int n;

ll cnt[maxn], dp[maxn], new_dp[maxn];

int sinal(int x) { return x == (n-1)/2 ? 0 : x < (n-1)/2 ? -1 : 1; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 0, h; j < n; j++) {
			scanf("%d", &h); a[i].pb(h); todos.pb({h, i});
		}
	}
	sort(all(todos));
	for(auto p : todos) {
		auto [h, ind] = p;
		++cnt[ind];
		memset(dp, 0, sizeof dp);
		memset(new_dp, 0, sizeof new_dp);
		dp[0] = 1;
		for(int j = 1; j <= n; j++) {
			if(j == ind) continue;
			new_dp[0] = dp[0] * (n - cnt[j]);
			for(int q = 1; q <= n; q++) {
				new_dp[q] = dp[q] * (n - cnt[j]) % mod;
				add(new_dp[q], dp[q-1] * cnt[j]);
			}
			for(int q = 0; q <= n; q++)
				dp[q] = new_dp[q], new_dp[q] = 0;
		}
		for(int q = 0; q <= n; q++)
			add(ans, 1ll * h * dp[q] * sinal(q) % mod);
	}
	printf("%lld\n", ans);
}