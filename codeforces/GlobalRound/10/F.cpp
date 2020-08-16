#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,a,b) for(int i = (a); i < b; i++)

int main() {
	int n; scanf("%d", &n);
	ll cap = 0;
	rep(i,0,n) {ll v; scanf("%lld", &v); cap += v-i;}
	ll k = cap%n;
	rep(i,0,n) printf("%lld ", cap/n + (k > 0) + i), k--;
	printf("\n");
}
