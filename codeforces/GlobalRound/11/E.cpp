#include<bits/stdc++.h>
using namespace std;

#define pb push_back
using ll = long long;

struct Opa
{
	ll a, b;
	bool t;
};

vector<Opa> resp;

void gcd(ll a, ll b, ll& x, ll& y) {
	if(!b) return (void)(x = 1, y = 0);
	gcd(b, a%b, x, y);
	ll sv = y;
	y = x - (a/b) * y;
	x = sv;
}

void mult(ll b, ll e) {
	ll ans = 0;
	while(1) {
		if(e&1) {if(ans>0) resp.pb({ans, b, 1}); ans += b;}
		e >>= 1;
		if(!e) break;
		resp.pb({b, b, 1});
		b += b;
	}
}


int main() {
	int x; scanf("%d", &x);
	int msb = 31 - __builtin_clz(x);
	ll a = 1ll*x*(1 << msb);
	mult(1ll*x, 1 << msb);
	ll val = a^x;
	resp.pb({a, x, 0});
	ll X, Y; gcd(x, val, X, Y);
	if(X < 0) X = -X;
	else Y = -Y;
	mult(x, X); mult(val, Y);
	a = x * X; ll b = val * Y;
	if(a > b)
		swap(a, b);
	if(a&1) {
		resp.pb({a, x, 1});
		resp.pb({b, x, 1});
		a += x, b += x;
	}
	resp.pb({a, b, 0});
	printf("%d\n", (int)(resp.size()));
	for(auto R : resp) {
		if(R.t) printf("%lld + %lld\n", R.a, R.b);
		else printf("%lld ^ %lld\n", R.a, R.b);
	}
}