#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	int n;
	cin >> n;
	cout << n;
	for(int i = 1; i < t; i++){
		cin >> n;
		cout << ' ' << n;
	}
	cout << endl;
	return 0;
}
