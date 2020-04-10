#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

vector<ll> vec;

int count(int n, ll v){
	int ans = 0;
	for(int i = 0; i < n; i++){
		if(vec[i] <= v) ans++;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, ans = 0;
	cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++){
		ll x, y;
        cin >> x >> y;
        vec[i] = x*x + y*y;
        ans += count(i, vec[i]);
    }
    cout << ans << endl;
}
