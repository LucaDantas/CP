/*

	General lagrange for O(k^2) per computation
	In this case we interpolate the function of sum of powers
	1^k + 2^k + 3^k + ... n^k

	This works because this function yields a polynomial of k+1-th
	degree, so we need k+2 points to be able to interpolate
	It is also important to notice that for the set of points
	generated there exists only one possible polynomial, which means
	that it'll find the answer for any value of n we throw at it

	https://en.wikipedia.org/wiki/Polynomial_interpolation#Uniqueness_of_the_interpolating_polynomial
	for proof

*/

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int mod = 1e9+7;
constexpr int maxn = 1e4+10;

int k;

// quero calcular 1^k + 2^k + ... n^k

// dá pra fazer uma interpolação de lagrange já que isso é um polinomio
// de k+1 grau, então a gente monta lagrange com k+2 pontos

int power(ll b, int e) {
	ll ans = 1;
	while(e) {
		if(e&1) ans *= b, ans %= mod;
		b *= b, b %= mod;
		e >>= 1;
	}
	return (int)ans;
}

int y[maxn];

int lagrange(int x) {
	int ans = 0;
	for(int i = 1; i <= k+2; i++) {
		ll here = 1;
		for(int j = 1; j <= k+2; j++) {
			if(i == j) continue;
			here *= 1ll * (x - j) * power(i - j, mod-2) % mod;
			here %= mod;
		}
		ans += 1ll * y[i] * here % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main() {
	int n;
	cin >> n >> k;
	int val = 0;
	for(int i = 1; i <= k+2; i++) {
		val += power((ll)i, k);
		if(val >= mod) val -= mod;
		y[i] = val;
	}
	cout << lagrange(n) << endl;
}