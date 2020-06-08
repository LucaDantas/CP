#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n, f, s;
	cin >> n;
	ll ans = 1;
	for(ll i = 0, a; i < n; i++){
		cin >> a;
		if(i==0) f = a;
		if(i==1) s = a;
		if(i >= n-3) ans *= a;
		if(i == n-1) ans = max(ans, f*s*a);
	}
	cout << ans << endl;
}
