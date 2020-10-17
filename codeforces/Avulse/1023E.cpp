#include<bits/stdc++.h>
using namespace std;

#define pb push_back

int n;

int query1(int r, int c) {
	cout << "? 1 1 " << r << ' ' << c << endl;
	string ans;
	cin >> ans;
	if(ans == "BAD") assert(0);
	return ans == "YES";
}

int query2(int r, int c) {
	cout << "? " << r << ' ' << c << ' ' << n << ' ' << n << endl;
	string ans;
	cin >> ans;
	if(ans == "BAD") assert(0);
	return ans == "YES";
}

int main() {
	cin >> n;

	int r = n, c = n;
	vector<int> ff, ss;
	for(int i = 1; i < n; i++)
		if(query1(r-1, c))
			r--, ss.pb(1);
		else c--, ss.pb(0);
	reverse(ss.begin(), ss.end());
	
	r = c = 1;
	for(int i = 1; i < n; i++)
		if(query2(r, c+1))
			c++, ff.pb(0);
		else r++, ff.pb(1);

	cout << "! ";
	for(auto it : ff)
		cout << (it?"D":"R");
	for(auto it : ss)
		cout << (it?"D":"R");
	cout << endl;
}