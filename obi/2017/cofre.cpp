#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MAXN 100100

int pref[10][MAXN]; //prefix sum from 1..9
int ans[10] = {0};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, val, cur, last, first;
	cin >> n >> m;
	for(int i = 0;i < 10; i++) pref[i][0] = 0;
	for(int i = 1; i <= n; i++){
		for(int k = 0; k < 10; k++) pref[k][i] = pref[k][i-1];
		cin >> val;
		pref[val][i]++;
		if(i==1) first = val;
	}
	cin >> last;
	ans[first]++;
	for(int i = 1; i < m; i++){
		cin >> cur;
		if(cur > last) for(int k = 0; k < 10; k++) ans[k] += pref[k][cur] - pref[k][last];
		else for(int k = 0; k < 10; k++) ans[k] += pref[k][last-1] - pref[k][cur-1];
		last = cur;
	}
	cout << ans[0];
	for(int i = 1; i < 10; i++) cout << ' ' << ans[i];
	cout << endl;
}
