#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e6 + 10;
constexpr int SQRT = 15e8;
constexpr int mod = 998244353;

ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

vi pr;

bool fact[MAXN];

void sieve() {
	for(int i = 2; i*i < MAXN; i++) {
		if(!fact[i]) {
			for(int k = i*i; k < MAXN; k += i) {
				fact[k] = 1;
			}
		}
	}
	rep(i,2,MAXN) if(!fact[i]) pr.pb(i);
}

bool perfect_square(ll x) {
	int l = 1, r = SQRT, ans = 0;
	while(l <= r) {
		int m = l + (r-l)/2;
		if(1ll*m*m >= x)
			r = m-1, ans = m;
		else
			l = m+1;
	}
	return 1ll*ans*ans == x;
}

map<ll, int> mp;

int main() {
	sieve();
	int n; scanf("%d", &n);
	vector<ll> a(n);

	rep(i,0,n) scanf("%lld", &a[i]);

	rep(i,0,n) {
		for(auto p : pr) {

			bool cut = 0;
			while(a[i]%p == 0) {
				mp[p]++;
				cut = 1;
				a[i] /= p;
			}

			if(a[i] == 1) break;

			if(cut) {
				mp[a[i]]++;
				a[i] = 1;
				break;
			}
		}
	}

	// we made it in such a way that the only numbers left are those who have big values
	// divisors only, if any number has a divisor <= 2e6 we've already killed him 

	map<ll, int> s;

	rep(i,0,n) {
		if(a[i] == 1) continue;
		s[a[i]]++;
	}

	vector<pair<ll,int>> cnt;
	for(auto it = s.begin(); it != s.end(); ++it) {
		cnt.pb({it->first, it->second});
	}

	ll ans = 1;

	for(int i = 0; i < sz(cnt); i++) {

		ll val = cnt[i].ff;
		int times = cnt[i].ss;
		bool done = 0;

		for(int j = 0; j < sz(cnt); j++) {

			if(i == j) continue;

			ll GCD = gcd(val, cnt[j].ff);

			if(GCD > 1) {
				mp[val/GCD] += times;
				mp[GCD] += times;
				done = 1;
				break;
			}
		}

		if(!done) {
			if(perfect_square(val)) ans *= (2*times+1);
			else ans *= (times+1)*(times+1);
			ans %= mod;
		}
	}

	for(auto it = mp.begin(); it != mp.end(); ++it) {
		ans *= it->ss+1;
		ans %= mod;
	}

	printf("%lld\n", ans);
}

// Solution:

// We want to separete into a few groups. First we select the ones that have some
// prime divisor <= 2e6. We'll first count the number of divisors in the smallest group
// and as we go if there is a prime divisor <= 2e6 we already kill him. If it has no
// divisor in this interval it goes to the other group. An important thing to notice
// is that if a number goes to this next group it is either in the for p², or in the
// form x*y, where p, x, y are primes and k == 2.

// Then we're going to do a check by comparing the gcd of every pair in the second group.
// If there is a gcd with someone else that is different from him then we create a class in a
// set containing the number of times that guy appears, if some of the divisors do not
// appear we simply multiply the total value by the number of times it appears + 1.
// We also need to be careful in case it is a perfect square because instead of
// multiplying the answer by (times+1)² we multiply it by 2*times+1.
// Wwe can't know what that number is but we simply don't care because it was
// counted on to the total number of dvisors already, if the gcd of other two guys
// is not 1 we can simply add it as a class and count because we know what is that
// divisor of it
