#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define pii pair<int, int>
const int maxn = 1e5 +  100;

void solve(){
	int h, n, m;
	cin >> h >> n >> m;
	while(h > 20 && n > 0){
		h /= 2;
		h += 10;
		n--;
	}
	while(h > 0 && m > 0){
		h-=10;
		m--;
	}
	if(h <= 0) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--) solve();
}
