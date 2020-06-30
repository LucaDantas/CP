#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

//we must see that for us to have a valid array
//all the values must not be coprime, that is
//gcd(a1,a2,..,an) != 1 --> a1 | gcd(a1,a2,..,an)
//where the elements are in increasing order

//which means that we want to find the number of
//multiples of every initial value <= n, and if there
//is at least k items we add to the answer
// (n/val) choose k, where n/val is the number of
//multiples of the first value (aka a1)

const int maxn = 5e5 + 100, mod = 998244353;

ll fat[maxn];

void calc() {
	fat[0] = 1;
	rep(i,1,maxn) {
		fat[i] = fat[i-1] * i % mod;
	}
}

ll power(ll b, ll e) {
	ll ans = 1;
	b %= mod;
	while(e > 0) {
		if(e&1)
			ans = ans*b%mod;
		e >>= 1;
		b = b*b%mod;
	}
	return ans;
}

ll inv(ll x) {
	return power(x,mod-2);
}

int main(){
	ll n, k;
	scanf("%lld %lld", &n, &k);
	
	calc();
	
	ll ans = 0;
	
	for(int i = 1; n/i >= k; i++) {
		int mult = n/i;
		ans = (ans + fat[mult-1]*inv(fat[k-1]*fat[mult-k]%mod))%mod;
	}
	
	printf("%lld\n", ans);
}
