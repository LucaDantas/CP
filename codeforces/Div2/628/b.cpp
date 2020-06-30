#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 1e5 + 100;

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int ans = n;
		vector<int> v(n);
		set<int> seen;
		for(auto &it : v)
			cin >> it;
		for(auto &it : v){
			if(seen.find(it) != seen.end()) ans--;
			else seen.insert(it);
		}
		cout << ans << endl;
	}
}
