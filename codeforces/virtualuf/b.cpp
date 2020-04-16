#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 100;
int a[maxn];
//vector<bitset<maxn> > tab(maxn);

void solve(){
	int n;
	bool ans = false;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			if(a[i] == a[j])
				if(j-i > 1) ans = true;
	if(ans) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main(){
	int t;
	cin >> t;
	while(t--) solve();
}
