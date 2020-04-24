#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, ans;
    cin >> n;
    int l = 0, r = n-1;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
		cin >> v[i];
	}
	cin >> ans;
	while(v[l]+v[r] != ans){
		if(v[l]+v[r] > ans) r--;
		else l++;
	}
	cout << v[l] << ' ' << v[r] << endl;
}

