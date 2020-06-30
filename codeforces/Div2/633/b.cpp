#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100100

int a[MAXN], ans[MAXN];

void solve(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a, a+n);
	int l = 0, r = n-1;
	for(int i = 0; i < n; i++){
		if(i%2 == 0) ans[i] = a[l++];
		else ans[i] = a[r--];
	}
	reverse(ans, ans + n);
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << ' ' << ans[i];
	cout << '\n';
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		solve();
	}
	return 0;
}
