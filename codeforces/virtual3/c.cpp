#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((ll)(a).size())
#define rep(i,a,b) for(ll i=(a); i<(b); i++)
#define dec(i,n,a) for(ll i=(n); i>=(a); i--)
#define read(v, a, b) for(ll i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(ll i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const ll maxn = 3e5 + 100;
const ll inf = 1e18;

ll a[maxn], b[maxn];

int main(){
	FAST;
	ll t;
	cin >> t;
	while(t--){
		ll n;
		cin >> n;
		for(ll i = 0; i < n; i++){
			cin >> a[i] >> b[i];
		}
		ll ans = 0, mn = inf;
		rep(i, 0, n){
			ll ni = (i+1)%n;
			ans += max(0LL, a[ni] - b[i]);
			mn = min(mn, min(a[ni], b[i]));
		}
		cout << ans + mn << endl;
	}
}
