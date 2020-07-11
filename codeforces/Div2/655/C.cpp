#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;

#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)

int main() {
	int t; cin >> t;

	rep(tt,0,t) {
		int n; cin >> n;
		vi a(n); rep(i,0,n) cin >> a[i];

		int ini = 0, fim = n+1;
		rep(i,0,n) {
			if(a[i] == i+1) ini = i+1;
			else break;
		}
		dec(i,n-1,0) {
			if(a[i] == i+1) fim = i+1;
			else break;
		}

		if(ini == n) {
			cout << "0\n";
			continue;
		}

		bool gut = 1;
		rep(i,ini, fim-1) if(a[i] == i+1) gut = 0;
		cout << (gut? "1\n":"2\n");
	}
}
