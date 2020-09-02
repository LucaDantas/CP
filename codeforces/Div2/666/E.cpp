#include<bits/stdc++.h>
using namespace std;

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;
using ll = long long;
#define ff first
#define ss second

// a -> pistola
// b -> laser
// c -> awp
// d -> teleporte

// sempre que usado o laser deve ser considerado como min(b, a*(qtd+1))

// matar brute -> mata todo mundo fraco na pistola e depois o gigante na awp
// custo == qtd * a + c 

// matar com o laser + pistola (solo) -> dá um tiro de laser, volta/anda, dá uma pistola
// custo == min(b,(qtd+1)*a) + 2*d + a

// matar com o laser (pares) -> laser, anda, laser, anda, pistola, anda, pistola
// custo == 2*b + 2*d + 2*a (mata duas posições independente do valor)

// matar com pistola + brute (pares) -> laser, anda, pistola*qtd + awp, volta, pistola
// custo == b + a + a*qtd + c + 2*d

int main() {
	ll n, a, b, c, d;
	scanf("%lld %lld %lld %lld %lld", &n, &a, &b, &c, &d);
	
	vector<ll> numb(n);
	for(ll& x : numb)
		scanf("%lld", &x);

	a = min(a, c);
	c = min(c, 2*(a+d));

	// first é sem ter me usado como parte do passado e second é tendo usado
	pair<ll,ll> dp, new_dp;

	for(int i = 0; i < n; i++) {
		new_dp.ff = min({(i>0?dp.ss:inf), dp.ff + min(numb[i]*a + c, min(b,(numb[i]+1)*a) + 2*d + a)}) + (i<n-1?d:0);
		if(i < n-1) new_dp.ss = dp.ff + min(2*(d+a) + min(b,(numb[i]+1)*a) + min(b,(numb[i+1]+1)*a), min(b,(numb[i]+1)*a) + a + a*numb[i+1] + c + 2*d - (i==n-2?d:0)) + d;
		else new_dp.ss = 0;
		swap(dp, new_dp);
	}
	printf("%lld\n", dp.ff);
}