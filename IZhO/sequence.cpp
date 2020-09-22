/*

	Define dp[left][right][y] = the best value for a value with mask equal
	to left, whose right submask's and has exactly y values turned on

	So when getting the value of current dp we can brute the left mask
	we want and that uniquely defines the right segment
	
	And when we want to update the dp we can brute the right segment
	because the left is already defined
	
*/


#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define ff first
#define ss second

#define pb push_back

constexpr int maxn = 1e5+10;

int a[maxn], k[maxn], n;

int dp[1<<10][1<<10][11]; // left submask, right submask, y

int ant[maxn], pos[1<<10][1<<10][11];

void print(int ans) {
	vector<int> resp;
	while(ans) {
		resp.pb(ans);
		ans = ant[ans];
	}
	reverse(resp.begin(), resp.end());
	for(auto it : resp)
		printf("%d ", it);
	printf("\n");
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &k[i]);
	
	int ans = 0, id = 0;

	for(int i = 1; i <= n; i++) {
		int here = 1, l = 0, r = 0;
		
		for(int lg = 0; lg < 10; lg++)
			l += ((1<<lg)&a[i]);
		for(int lg = 10; lg < 20; lg++)
			r += ((1<<lg)&a[i]);
		r >>= 10;

		// Updating my dp value
		for(int mask = 0; mask < (1 << 10); mask++) {
			int y = k[i] - __builtin_popcount(l&mask);
			if(y >= 0 && y <= 10 && dp[mask][r][y] >= here)
				here = dp[mask][r][y]+1, ant[i] = pos[mask][r][y];
		}

		// Updating the dp array
		for(int mask = 0; mask < (1 << 10); mask++) {
			int y = __builtin_popcount(r&mask);
			if(dp[l][mask][y] < here)
				dp[l][mask][y] = here, pos[l][mask][y] = i;
		}

		if(here > ans)
			ans = here, id = i;
	}	

	printf("%d\n", ans);
	print(id);
}