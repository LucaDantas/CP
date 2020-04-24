#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MAXD 134217728

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, f;
    cin >> n >> f;
    vector<int> c(n);
    for(int i = 0; i < n; i++){
		cin >> c[i];
	}
	int l = 0, r = MAXD, ans = MAXD;
	while(l <= r){
		int mid = l + (r-l)/2, sum = 0;
		for(int i = 0; i < n; i++){
			sum+=mid/c[i];
		}
		if(sum >= f){
			ans = mid;
			r = mid-1;
		}
		else l = mid+1;
	}
	cout << ans << endl;
}
