/*

	Baricentric implementation of lagrange interpolation
	O(k^2) precomputation and O(k) per query

	ps: in this case we exploit a special case which makes it possible
	to do the precomputation in O(k) instead of O(k^2)

	We first compute l(x) for the given value, which is defined
	by (x - x_1) * (x - x_2) * ... * (x - x_k)
	[ π {1 <= i <= k} (x - x_i) ]

	we also define l_i(x_i) for 1 <= i <= k
	[ π {1 <= j <= k, i != j} (x_i - x_j) ]
	if we consider x_i - x_i for any i of course the product will be zero
	and we don't want that

	let's define w_i = l_i(x_i)^(-1)

	That way we can rewrite the typical formula to:

	L(x) = l(x) * [Σ (w_i * y_i) / (x - x_i) ]



	In this case we want to calculate f(n, k) = 1^k + 2^k + ... n^k

	we use the points x_1 = 1, x_2 = 2, ... x_k+2 = k+2
	that way we can easily calculate (in O(k)) the correspondent
	y values

*/

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxk = 1e6+10;
constexpr int mod = 1e9+7;

ll y[maxk], fat[maxk], w[maxk];
ll x, k;

ll power(ll b, ll e) {
	ll ans = 1;
	while(e) {
		if(e&1) ans *= b, ans %= mod;
		b *= b, b %= mod;
		e >>= 1;
	}
	return ans;
}

int main() {
	scanf("%lld %lld", &x, &k);
	ll val = 0; fat[0] = 1;
	for(int i = 1; i <= k+2; i++) {
		val += power(i, k);
		if(val >= mod) val -= mod;
		y[i] = val;
		fat[i] = fat[i-1] * i % mod;
	}
	if(x <= k+2) {printf("%lld\n", y[x]); return 0;}
	
	for(int i = 1; i <= k+2; i++) {
		/*Regular way of doing it
		w[i] = 1;
		for(int j = 1; j <= k+2; j++) {
			if(i == j) continue;
			w[i] *= (i - j);
		}
		cout << w[i] << endl;
		w[i] = power(w[i], mod-2);*/

		
		// we can notice for this special case where x_i = i
		// the value of l_i(x_i) is (i-1) * (i-2) * ... * 1 * -1 * -2 * ... * (k - i)
		// and we can determine the sign by the parity

		w[i] = fat[i-1] * fat[k+2-i] % mod;
		if((k+2-i)&1) w[i] = mod - w[i];
		w[i] = power(w[i], mod-2);
	}

	ll ans = 0, lx = 1;

	for(int i = 1; i <= k+2; i++) {
		lx *= 1ll*(x-i), lx %= mod;
		ans += (w[i] * power(x - i, mod-2) % mod) * y[i] % mod;
		if(ans >= mod) ans -= mod;
	}

	printf("%lld\n", ans * lx % mod);
}