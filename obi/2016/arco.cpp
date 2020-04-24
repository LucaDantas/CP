#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
ll x, y;
vector<ll> vec;

ll merge(vector<ll> &v){
	ll n = (ll)v.size();
	if(n <= 1) return 0;
	vector<ll> u1, u2;
	for(ll i = 0; i < n/2; i++){
		u1.push_back(v[i]);
	}
	for(ll i = n/2; i < n; i++){
		u2.push_back(v[i]);
	}
	ll inv = merge(u1) + merge(u2);
	u1.push_back(-1);
	u2.push_back(-1);
	ll p1=0, p2=0;
	//We have to order in decreasing order for it to work
	for(ll i = 0; i < n; i++){
		if(u2[p2] >= u1[p1]){
			//It means that there was an inversion here
			inv += (ll)u1.size() - p1 - 1;
			v[i] = u2[p2++];
		}
		else v[i] = u1[p1++];
	}
	return inv;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> x >> y;
		vec.push_back(x*x + y*y);
	}
	ll ans = merge(vec);
	cout << ans << endl;
}
