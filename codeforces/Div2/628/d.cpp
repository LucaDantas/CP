#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 1e5 + 100;

vector<ll> ans;

int power2(ll x){
	for(ll i = 1, r1 = 1; i < 63; i++){
		if((r1<<i) > x) return i-1;
	}
	cout << "KKK" << endl;
	return 62;
}

bool isSet(ll x, ll i){
	ll r1=1;
	if((x&(r1<<i)) == x) return true;
	return false;
}

int main(){
	FAST;
	ll u, v;
	cin >> u >> v;
	if(u > v || (v-u)%2 == 1) cout << -1 << endl;
	else if(v == 0) cout << 0 << endl;
	else if(u == v) cout << 1 << endl << u << endl;
	else{
		ans.pb(u);
		ll calc = (v-u)/2;
		if((u&calc) == 0) ans[0] = u|calc;
		else ans.pb(calc);
		ans.pb(calc);
		cout << ans.size() << endl;
		for(auto it : ans){
			cout << it << ' ';
		}
		cout << endl;
	}
}
