#include<bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		vector<int> a(n+m);
		for(int i = 0; i < n; i++)
			for(int j = 0, x; j < m; j++)
				scanf("%d", &x), a[i+j] ^= x;
		int ans = 0;
		for(int x : a)
			ans |= x;
		puts(ans?"Ashish":"Jeel");
	}
}