#include<bits/stdc++.h>
using namespace std;

int main() {
	vector<int> v(8);
	for (int i = 0; i < 8; i++) {
		cin >> v[i];
		if (v[i] == 9) {
			cout << "F\n";
			return 0;
		}
		
	}
	cout << "S\n";
}
