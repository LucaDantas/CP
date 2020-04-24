#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int maxn = 5e5 + 100;
ll a[maxn], pref[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k, ans=0;
	cin >> n >> k;
	for(ll i = 1; i <= n; i++)
		cin >> a[i];
	for(ll i = 1; i <= n; i++)
		pref[i] = pref[i-1] + a[i];
	for(ll i = 1; i <= n; i++)
		ans += upper_bound(pref+i, pref + n+1, pref[i-1]+k) - lower_bound(pref+i, pref + n+1, pref[i-1]+k);
	cout << ans << endl;
}
