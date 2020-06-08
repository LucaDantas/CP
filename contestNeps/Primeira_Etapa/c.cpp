#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>

vector<ll> a;

//ll create(ll i){
	//ll p1 = a[i], p2 = a[i+1], p3 = a[i+2];
	//ll p = (p1+p2+p3)/2;
	//ll area = p*(p-p1)*(p-p2)*(p-p3);
	//return area;
//}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n, ans = 0;
	ll maxarea = 0;
	cin >> n;
	a.resize(n);
	for(ll i = 0; i < n; i++)
		cin >> a[i];
	sort(a.begin(), a.end(), greater<ll>());
	for(ll i = 0; i < n-2; i++){
		if(a[i+1] + a[i+2] > a[i]){
			double area = sqrt(1.00*a[i+1]*a[i]*a[i+2]);
			if(area > maxarea){
				maxarea = area;
				ans = i;
			}
		}			
	}
	cout << a[ans+2] << ' ' <<  a[ans+1] << ' ' << a[ans] << endl;
}
