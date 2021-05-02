#include <bits/stdc++.h>
#include "books.h"
using namespace std;

constexpr int logn = 20, maxn = 2e5+10;

long long dp[maxn];

long long get(int x) {
	if(dp[x] != -1) return dp[x];
	dp[x] = skim(x);
	return dp[x];
}

void solve(int N, int k, long long A, int S) {
	memset(dp, -1, sizeof dp);
	int pos = N+1;
	int l = 1, r = N;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(get(m) >= A) pos = m, r = m-1;
		else l = m+1;
	}
	
	if(pos < k) impossible();

	long long menores = 0;
	for(int i = 1; i < k; i++) {
		menores += get(i);
		if(menores > 2*A) impossible();
	}
	
	if(pos <= N && menores + get(pos) <= 2*A) {
		vector<int> ans;
		for(int i = 1; i < min(k, pos); i++)
			ans.push_back(i);
		ans.push_back(pos);
		answer(ans);
		return;
	}

	if(pos == k) impossible();

	N = pos - 1;

	for(int i = 0; i <= k; i++) {
		long long sum = 0;
		vector<int> ans;
		
		for(int j = 1; j <= i; j++)
			sum += get(j), ans.push_back(j);
		
		for(int j = N - k + i + 1; j <= N; j++)
			sum += get(j), ans.push_back(j);

		if(sum >= A && sum <= 2*A)
			answer(ans);
	}

	impossible();
}