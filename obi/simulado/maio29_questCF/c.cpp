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

const int maxn = 1e5 + 100;

// up to 64 only

ll power(ll base, ll expo) {
	ll ans = 1;
	rep(i,0,expo)
		ans *= base;
	return ans;
}

int soma(ll valor) {
	int ret = 0;
	string v = to_string(valor);
	allin(c, v) {
		ret += c-'0';
	}
	return ret;
}

int main(){
	ll a, b, c;
	scanf("%lld %lld %lld", &a, &b, &c);
	vll ans;
	
	for(ll s = 1; s <= 81; s++) {
		ll valor = b * power(s, a) + c;
		if(valor > 0 && valor <= 1000000000 && soma(valor) == s)
			ans.pb(valor);
	}
	printf("%d\n", sz(ans));
	rep(i,0,sz(ans))
		printf("%lld%c", ans[i], " \n"[i==sz(ans)-1]);
}
