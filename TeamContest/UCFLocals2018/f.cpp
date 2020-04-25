#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

ll pow2(ll x){
	ll ans = 0;
	for(; x%2 == 0; x /= 2)
		ans++;		
	return ans;
}

ll pow5(ll x){
	ll ans = 0;
	for(; x%5 == 0; x /= 5)
		ans++;		
	return ans;
}

ll power2(ll t){
	ll p =1;
	for(ll i = 0; i < t; i++)
		p *= 2;
	return p;
}

ll power5(ll t){
	ll p =1;
	for(ll i = 0; i < t; i++)
		p *= 5;
	return p;
}

int main(){
	FAST;
	ll p2, p5, n;
	vll ans;
	cin >> n;
	p2 = pow2(n);
	p5 = pow5(n);
	cout << (p2+1)*(p5+1) << endl;
	for(ll i = 0; i <= p2; i++)
		for(ll j = 0; j <= p5; j++)
			ans.pb(power2(i)*power5(j));
	sort(all(ans));
	for(auto fudido : ans) cout << fudido << endl;
}
