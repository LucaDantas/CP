#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 2e5+10, mod = 998244353;

int cnt[maxn], t[maxn], f[maxn], inv_f[maxn];

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

void calc() {
	inv_f[0] = f[0] = 1;
	for(int i = 1; i < maxn; i++)
		f[i] = (int)(1ll * i * f[i-1] % mod), inv_f[i] = power(f[i], mod-2);
}

struct BIT {
	int bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(; x > 0; x-=x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

int32_t main() {
	calc();
	int n, m; scanf("%lld %lld", &n, &m);
	for(int i = 0; i < n; i++) {
		int x; scanf("%lld", &x);
		++cnt[x];
	}
	for(int i = 0; i < m; i++)
		scanf("%lld", t+i);

	for(int i = 0; i < maxn; i++)
		if(cnt[i]) bit.upd(i, cnt[i]);
	
	int prod_inverso = 1;
	for(int letra = 0; letra < maxn; letra++)
		prod_inverso = (int)(1ll * prod_inverso * inv_f[cnt[letra]] % mod);

	int monstro = (int)(1ll * f[n-1] * prod_inverso % mod);

	int ans = 0;
	for(int i = 0; i < m; i++) {
		ans += (int)(1ll * monstro * bit.query(t[i]-1) % mod);
		if(!cnt[t[i]]) break;
		monstro = (int)(1ll * monstro * cnt[t[i]] % mod); // essa letra agora tem uma pessoa a menos
		monstro = (int)(1ll * monstro * power(n-1-i, mod-2) % mod); // reduzo o fatorial do monstro
		--cnt[t[i]];
		bit.upd(t[i], -1);
	}
	printf("%lld\n", (ans + ((*max_element(cnt, cnt+maxn)) == 0 && n < m)) % mod);
}
