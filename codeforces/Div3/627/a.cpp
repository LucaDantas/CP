#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
int a[maxn];

void solve(){
	int n, minn = 1000;
	bool ans = true;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++){
		minn = min(minn, a[i]);
	}
	for(int i = 0; i < n; i++)
		if((a[i] - minn)%2 == 1) ans = false;
	if(ans) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main(){
	int t;
	cin >> t;
	while(t--)
		solve();
}
