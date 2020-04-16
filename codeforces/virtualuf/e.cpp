#include<bits/stdc++.h>
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

const int maxn = 2010;

int n, hours, l, r;
int a[maxn], tab[maxn][maxn];

int dp(int i = 0, int h = 0){
	if(i==n) return tab[i][h] = (h >= l && h <= r) ? 1 : 0;
	if(tab[i][h] != -1) return tab[i][h];
	int good = (h >= l && h <= r && i != 0) ? 1 : 0;
	int normal = dp(i+1, (h+a[i])%hours);
	int m1 = dp(i+1, (h+a[i]-1)%hours);
	good += max(normal, m1);
	return tab[i][h] = good;
}

int main(){
	FAST;
	cin >> n >> hours >> l >> r;
	memset(tab, -1, sizeof tab);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	cout << dp() << endl;
}
