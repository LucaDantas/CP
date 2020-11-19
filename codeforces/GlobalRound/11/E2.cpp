#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define sz(a) (int)(a.size())

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  k = (T) rng();
  return (T) (((k % v) + v) % v);
}

struct Opa
{
	ll a, b;
	bool t;
};

vector<Opa> resp;

vector<ll> base;

ll check(ll x) {
	for(ll v : base)
		x = min(x, x^v);
	return x;
}

void add(ll x) {
	for(ll v : base)
		if((x^v) < x)
			resp.pb({x, v, 0}), x ^= v;
}

int main() {
	ll x; scanf("%lld", &x);
	base.pb(x);
	while(check(1)) {
		ll a = base[rnd(sz(base))], b = base[rnd(sz(base))];
		if(a + b > (1ll << 40)) continue;
		ll opa = check(a + b);
		if(opa) {
			resp.pb({a, b, 1});
			add(a+b);
			base.pb(opa);
		}
	}
	printf("%d\n", sz(resp));
	for(auto R : resp) {
		if(R.t) printf("%lld + %lld\n", R.a, R.b);
		else printf("%lld ^ %lld\n", R.a, R.b);
	}
}
