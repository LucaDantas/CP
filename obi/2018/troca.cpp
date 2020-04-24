#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 100;
int pref[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	int cima[maxn], baixo[maxn];
	for(int i = 1; i <= n; i++){
		cin >> cima[i];
	}
	for(int i = 1; i <= n; i++){
		cin >> baixo[i];
	}
	for(int i = 1; i <= k; i++){
		int l, r;
		cin >> l >> r;
		pref[l]++;
		pref[r+1]--;
	}
	for(int i = 1; i <= n; i++){
		pref[i] += pref[i-1];
	}
	if(pref[1]%2 == 0) cout << cima[1];
	else cout << baixo[1];
	for(int i = 2; i <= n; i++){
		if(pref[i]%2 == 0) cout << ' ' << cima[i];
		else cout << ' ' << baixo[i];
	}
	cout << endl;
}
