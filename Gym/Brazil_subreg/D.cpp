#include<bits/stdc++.h>
using namespace std;


pair<int, int> transform(pair<int, int> pos, int n) {
	if (pos.first > n / 2) {
		pos.first = n - pos.first;
	}
	if (pos.second > n / 2) {
		pos.second = n - pos.second;
	}
	
	return pos; 
	
	
}

pair<int, int> project(pair<int, int> pos, int n) {
	pos = transform(pos, n);
	pos.first *= 2;
	pos.second *= 2;
	return pos;
} 

int main() {
	int n;
	int x, y;
	cin >> n >> x >> y;
	n = 1 << n;
	pair<int, int> pos = make_pair(x, y);
	
	int ans = 0;
	
	while (pos != make_pair(n/2, n/2)) {
		ans++;
		pos = project(pos, n);
		
	}
	
	cout << ans << '\n';
}

