#include<bits/stdc++.h>
using namespace std;
#include "prize.h"

#define pb push_back
#define sz(a) (int)((a).size())

const vector<int> good = {0, 0};

constexpr int maxn = 2e5+10;

map<int,set<int>> s;
int ans[maxn];

int solve(int l, int r) {
	if(l > r) return -1;
	int m = (l+r) >> 1;
	vector<int> get = ask(m);
	if(get == good) return m;
	ans[m] = get[0];
	auto it = s[get[0]+get[1]].insert(m).first;
	if(it == s[get[0]+get[1]].begin() || ans[*prev(it)] != ans[m]) {
		int ans = solve(l, m-1);
		if(ans != -1) return ans;
	}
	if(it == --s[get[0]+get[1]].end() || ans[*next(it)] != ans[m]) {
		int ans = solve(m+1, r);
		if(ans != -1) return ans;
	}
	return -1;
}

int find_best(int n) {
	return solve(0, n-1);
}
