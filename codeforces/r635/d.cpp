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

int v1[maxn], v2[maxn], v3[maxn];

void solve(){
	FAST;
	int n1, n2, n3;
	cin >> n1 >> n2 >> n3;
	for(int i = 0; i < n1; i++)
		cin >> v1[i];
	for(int i = 0; i < n2; i++)
		cin >> v2[i];
	for(int i = 0; i < n3; i++)
		cin >> v3[i];
	sort(v1, v1+n1);
	sort(v2, v2+n2);
	sort(v3, v3+n3);
}

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--) solve();
}
