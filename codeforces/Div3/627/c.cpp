#include<bits/stdc++.h>
using namespace std;

void solve(){
	string s;
	int ans = 1, lastr = -1;
	cin >> s;
	for(int i = 0; i < (int)s.size(); i++){
		if(s[i] == 'L') ans = max(ans, i-lastr+1);
		else{
			lastr = i;
		}
	}
	cout << ans << endl;
}

int main(){
	int t;
	cin >> t;
	while(t--) solve();
}
