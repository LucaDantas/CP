#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100100
#define INF 1000000100

int a[MAXN];

int pot2(ll n){
	ll r1 = 1;
	for(ll i = 0; i < 63; i++){
		if(n <= (r1<<i)){
			return i;
		}
	}
	return 64;
}

void solve(){
	vector<int> pref;
	int n, maxdif = 0;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	for(int i = n-2; i >= 0; i--){
		if(a[i] > a[i+1]){
			maxdif = max(maxdif, a[i]-a[i+1]);
			pref.push_back(a[i]-a[i+1]);
		}
	}
	sort(pref.begin(), pref.end());
	int ans = max(pot2(maxdif), (int)pref.size());
	cout << ans << endl << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	for(int i = 1; i < t; i++){
		solve();
	}
	return 0;
}
