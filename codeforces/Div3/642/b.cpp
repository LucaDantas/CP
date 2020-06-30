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
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
		vi a(n), b(n), c;
		read(a,0,n);
		read(b,0,n);
		sort(all(a), greater<int>());
		sort(all(b), greater<int>());
		int ans = 0;
		rep(i,0,n-k)
			ans += a[i];
		rep(i, n-k, n)
			c.pb(a[i]);
		rep(i,0,n)
			c.pb(b[i]);
		sort(all(c), greater<int>());
		rep(i,0,k)
			ans += c[i];
		cout << ans << endl;
	}
}
