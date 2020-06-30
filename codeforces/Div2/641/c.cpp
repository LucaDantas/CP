#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,a,b) for(int i=(a); i>=(b); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

ll lcm(ll a, ll b){
	return (a/__gcd(a,b))*b;
}

int main(){
	int n; scanf("%d", &n);
	vll a(n); read(a,0,n);
	vll pref(n), suf(n);
	pref[0] = a[0];
	suf[n-1] = a[n-1];
	rep(i,1,n) pref[i] = __gcd(a[i], pref[i-1]);
	dec(i, n-2,0) suf[i] = __gcd(a[i], suf[i+1]); 
	ll ans = lcm(suf[1], pref[n-2]);
	rep(i,1,n-1){
		ans = lcm(ans,__gcd(pref[i-1], suf[i+1]));
	}
	cout << ans << '\n';
}
