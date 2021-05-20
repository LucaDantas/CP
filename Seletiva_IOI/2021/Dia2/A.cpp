#include <bits/stdc++.h>
using namespace std;

#define int ll

using ll = long long;

using pii = pair<int,int>;

constexpr int mod = 1000000007, maxb = 60;

void add(int& a, long long b) { b %= mod; a += b; a %= mod; }

// int solo(ll x) {
// 	ll tam = 0;
// 	int ans = 0;
// 	for(int i = 40; i >= 0; i--) {
// 		if(x & (1ll << i)) add(ans, 2*tam/(1ll << i)+1), tam += (1ll << i);
// 		// if(x & (1ll << i)) add(ans, 2*tam/(1ll << i)+1), tam += (1ll << i), printf("%d %lld\n", i, tam);
// 	}
// 	return ans;
// }

int power(ll b, int e) {
	int ans = 1;
	b %= mod;
	while(e) {
		if(e&1) ans = (int)(1ll * b * ans % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int inv(ll v) { return power(v, mod-2); }

int dp[maxb][2], qtd[maxb][2], alturas[maxb][2];

bool on(long long v, int b) { return (v & (1ll << b)) > 0; }

int get(ll v) {
	int maior = 63 - __builtin_clzll(v);
	memset(dp, 0, sizeof dp);
	memset(qtd, 0, sizeof qtd);
	memset(alturas, 0, sizeof alturas);
	for(int b = maior; b >= 0; b--) {
		dp[b][b<maior] = 1;
		alturas[b][b<maior] = (1ll << b) % mod;
		qtd[b][b<maior] = 1;

		// ligar só com o anterior

		// me ligo pegando um 1
		add(dp[b][1], dp[b+1][1] + (2ll*alturas[b+1][1] * inv(1ll << b) % mod) + qtd[b+1][1]);
		// add(dp[b][1], 1ll*dp[b+1][1] + (2ll*alturas[b+1][1] * inv(1ll << b) % mod) + 1ll*qtd[b+1][1]);
		add(qtd[b][1], qtd[b+1][1]);
		add(alturas[b][1], alturas[b+1][1] + ((1ll << b) * qtd[b+1][1] % mod));

		// me ligo pegando um 0 anterior
		if(on(v, b)) {
			add(dp[b][0], dp[b+1][0] + (2ll*alturas[b+1][0] * inv(1ll << b) % mod) + qtd[b+1][0]);
			// add(dp[b][0], 1ll*dp[b+1][0] + (2ll*alturas[b+1][0] * inv(1ll << b) % mod) + 1ll*qtd[b+1][0]);
			add(qtd[b][0], qtd[b+1][0]);
			add(alturas[b][0], alturas[b+1][0] + ((1ll << b) * qtd[b+1][0] % mod));
		}

		// não me ligo
		add(dp[b][on(v, b)], 1ll*dp[b+1][0]);
		add(qtd[b][on(v, b)], qtd[b+1][0]);
		add(alturas[b][on(v, b)], alturas[b+1][0]);

		// não me ligo e pego do 1
		add(dp[b][1], 1ll*dp[b+1][1]);
		add(qtd[b][1], qtd[b+1][1]);
		add(alturas[b][1], alturas[b+1][1]);
		
		// printf("%d (%d %d) (%d %d) (%d %d)\n", 1<<b, qtd[b][0], qtd[b][1], alturas[b][0], alturas[b][1], dp[b][0], dp[b][1]);
	}
	return (dp[0][1] + dp[0][0]) % mod;
}

int pot[maxb];

int bro(int k) { return (1ll << k) % mod; }

// press f in the chat
int f(int k) {
	if(k == 0) return pot[k] = 1;
	return pot[k] = (2ll*f(k-1) + bro(k) + 2ll * (bro(k)) * (bro(k) - 1)) % mod;
}

int calc(ll v) {
	if(v <= 1) return v;
	int b = 63 - __builtin_clzll(v), ans = pot[b-1];
	ans += v - (1ll << b) + 1; // qtd do centro
	ll k = v - (1ll << b);
	ans += calc(k);
	for(int i = 0; i < b; i++) {
		if(on(v, i)) add(ans, bro(i) * bro(b - i));
		int val = (v >> i) << i; // rapar fora os menores
		if(!val) continue;
		add(ans, )
	}
}

int32_t main() {
	f(45);
	// ll l, r; scanf("%lld %lld", &l, &r);
	// printf("%lld\n", (get(r) - (l>1?get(l-1):0) + mod) % mod);
	// int n = 40;
	// printf("%lld %lld\n", f(n), get((1ll << n+1) - 1));
}