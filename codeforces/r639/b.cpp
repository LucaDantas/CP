#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

ll get(ll n){
	return (3LL*((n*(n+1))>>1)) - n;
}

ll bs(ll n){
	ll l = 0, r = 30000, ans=0; 
	while(l <= r){
		ll mid = ((l + r)>>1);
		if(get(mid) <= n){
			ans = get(mid);
			l = mid+1;
		}
		else{
			r = mid-1;
		}
	}
	return ans;
}

int main(){
	FAST;
	int T; cin >> T;
	while(T--){
		ll n; cin >> n;
		int ans=0;
		while(n>=2){
			ans++;
			n -= bs(n);
		}
		cout << ans << '\n';
	}
}
