#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e3+10, mod = 998244353;

struct BIT
{
	int bit[maxn][maxn];
	void upd(int x, int y, int v) {
		for(int i = x+1; i < maxn; i += i&-i)
			for(int j = y+1; j < maxn; j += j&-j)
				bit[i][j] += v, bit[i][j] %= mod;
	}
	int query(int x, int y) {
		int ans = 0;
		for(int i = x+1; i > 0; i -= i&-i)
			for(int j = y+1; j > 0; j -= j&-j)
				ans += bit[i][j], ans %= mod;
		return ans;
	}
} bit[2];

int main() {
	int n, m, ans = 0; scanf("%d %d", &n, &m);
	vector<int> a(n+1), b(m+1);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			if(a[i] != b[j]) continue;
			int v1 = bit[0].query(j-1, a[i]-1);
			int v2 = bit[1].query(j-1, maxn-5) - bit[1].query(j-1, a[i]);
			v2 = (v2 + mod) % mod;
			v1 = (v1 + mod) % mod;
			ans += (v1 + v2 + 1) % mod;
			if(ans < 0) ans += mod;
			else if(ans >= mod) ans -= mod;
			bit[1].upd(j, a[i], v1);
			bit[0].upd(j, a[i], v2 + 1);
		}
	}
	printf("%d\n", ans);
}