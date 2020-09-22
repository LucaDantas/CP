/*

	Classic exchange-arguments problem
	we need to find an ordering such that for every project that we receive
	we have at least its value, and after completing it our value changes
	by b[i]

	We can divide into two categories: either b_i is positive, which means
	that we want to use it as soon as possible to have the maximum health
	possible, or b[i] is negative, and we must find some ordering

	Let's use the technique of exchange arguments to find that ordering
	(b_i for every i is negative)	
	
	Suppose that for a given unordered pair (i, j) one way it works and the
	other doesn't, and we want to find which one is that one that works
	based on the values of a_i, b_i, a_j, b_j
	Note that if both orderings don't work or both work then it doesn't
	matter which one we choose because the effect is the same

	b_i < 0 && b_j < 0

	order 1 (i, j) -> works
	H >= a_i
	H + b_i >= a_j

	order 2 (j, i) -> doesn't work
	H >= a_j
	H + b_j < a_i

	Manipulate the inequations
	H + b_i - H - b_j > a_j - a_i
	b_i - b_j > a_j - a_i
	a_i + b_i > a_j + b_j

	So we have shown that if there is a pair in which only one of the ways
	works we know that it'll be when the one that has a greater a+b comes first
	If they have the same value I suppose it doesn't matter

*/

#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define a first
#define b second

constexpr int maxn = 110;

pii v[maxn];

int dp[maxn][maxn];

int main() {
	int n, h; scanf("%d %d", &n, &h);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &v[i].a, &v[i].b);
	sort(v+1, v+1+n, [](pii x, pii y){
		if(x.b >= 0 && y.b >= 0) return x.a < y.a;
		if(x.b >= 0) return true;
		if(y.b >= 0) return false;
		return x.a+x.b>y.a+y.b;
	});
	
	// we already have our ordering, now all that we need is to do a knapsack

	// dp[i][k] -> i == number we're on, k -> how many items taken
	// we want to maximize the health possible

	for(int i = 0; i <= n; i++)
		for(int k = 0; k <= n; k++)
			dp[i][k] = -0x3f3f3f3f;
	for(int i = 0; i <= n; i++)
		dp[i][0] = h;

	for(int i = 1; i <= n; i++)
		for(int k = 1; k <= n; k++)
			dp[i][k] = max(dp[i-1][k], (dp[i-1][k-1]>=v[i].a&&dp[i-1][k-1]+v[i].b>=0? dp[i-1][k-1] + v[i].b:-0x3f3f3f3f));
	
	bool ok = 0;
	for(int k = 0; k <= n; k++)
		if(dp[n][k] < 0) {
			printf("%d\n", k-1);
			ok = 1;
			break;
		}
	if(!ok) printf("%d\n", n);
}