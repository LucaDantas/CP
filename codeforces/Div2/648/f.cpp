#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vector<int> a(n), b(n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for(int i = 0; i < n; i++)
			scanf("%d", &b[i]);
		// It is important to notice that the pairs of elements i, n-i+1 never change
		// And that means they must be equal on a and b
		// We can also notice by considering only one side that what happens is that
		// we simply reverse a prefix that we choose, which means that we can put any
		// each pair wherever we want and choose which element goes on which side
		vector<pair<int,int>> pa, pb;
		for(int i = 0; i < n/2; i++) {
			pa.push_back({min(a[i], a[n-i-1]), max(a[i], a[n-i-1])});
			pb.push_back({min(b[i], b[n-i-1]), max(b[i], b[n-i-1])});
		}
		sort(pa.begin(), pa.end()); sort(pb.begin(), pb.end());
		if(pa != pb || (n&1 && a[n/2] != b[n/2]))
			puts("No");
		else
			puts("Yes");	
	}
}
