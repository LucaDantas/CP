#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

struct rect{
	rect(int xa, int ya, int xb, int yb){
		width = abs(xa-xb);
		top = max(ya,yb);
		bottom = min(ya,yb);
	}
	int width, top, bottom;
};

vector<rect> land;

ll count(int n){
	ll ans = 0;
	for(int i = 0; i < (int)land.size(); i++){
		if(n <= land[i].bottom) continue;
		if(n >= land[i].top) ans += (land[i].top - land[i].bottom)*land[i].width;
		else ans += (n-land[i].bottom)*land[i].width;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	for(int i = 0, xa, ya, xb, yb; i < n; i++){
		cin >> xa >> ya >> xb >> yb;
		rect a(xa,ya,xb,yb);
		land.push_back(a);
	}
	int beg = -(int)1e9 , end = (int)1e9;
	ll ans = end+100;
	while(beg <= end){
		int mid = beg + (end-beg)/2;
		ll num = count(mid);
		if(num >= k){
			ans = mid;
			end = mid-1;
		}
		else beg = mid+1;
	}
	if(ans > (int)1e9) cout << "PERDAO MEU REI"<< endl;
	else cout << ans << endl;
}
