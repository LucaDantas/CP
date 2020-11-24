#include<bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int d, k; scanf("%d %d", &d, &k);
		int l = 0, r = d/k, ans = -1;
		while(l <= r) {
			int m = (l+r) >> 1;
			if(2ll * k * k * m * m <= 1ll * d * d)
				ans = m, l = m+1;
			else r = m-1;
		}
		puts(1ll * ans * ans * k * k + 1ll * (ans+1) * (ans+1) * k * k <= 1ll*d*d?"Ashish":"Utkarsh");
	}
}