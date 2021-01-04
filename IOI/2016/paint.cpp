#include<bits/stdc++.h>
using namespace std;
#include "paint.h"

#define sz(a) (int)((a).size())
#define pb push_back

constexpr int maxn = 2e5+10, maxk = 110;

int dir[maxn], dp[maxn][maxk], mark[maxn], n;
string s;
vector<int> c;

struct BIT
{
	int bit[maxn];
	void itv(int l, int r) {
		++bit[l];
		--bit[r+1];
	}
	void sum() {
		for(int i = 1; i < maxn; i++)
			bit[i] += bit[i-1];
	}
	bool query(int x) {
		return bit[x] > 0;
	}
} bit;

bool solve(int pos, int j) {
	if(dp[pos][j] != -1) return dp[pos][j];
	if(pos >= n) return j == sz(c);
	dp[pos][j] = 0;
	if(j < sz(c) && pos + c[j] - 1 < dir[pos] && s[pos+c[j]] != 'X' && solve(pos + c[j] + 1, j+1))
		bit.itv(pos, pos + c[j] - 1), mark[pos+c[j]] = 1, dp[pos][j] = 1;
	if(s[pos] != 'X' && solve(pos+1, j))
		mark[pos] = 1, dp[pos][j] = 1;
	return dp[pos][j];
}

string solve_puzzle(string S, vector<int> C) {
	s = S; c = C;
	n = sz(s);
	dir[n] = n;
	for(int i = n-1; i >= 0; i--) {
		dir[i] = dir[i+1];
		if(s[i] == '_')
			dir[i] = i;
	}
	for(int i = 0; i < maxn; i++)
		for(int j = 0; j < maxk; j++)
			dp[i][j] = -1;
	solve(0, 0);
	string ans;
	bit.sum();
	for(int i = 0; i < n; i++) {
		if(bit.query(i) && mark[i]) ans.pb('?');
		else if(mark[i]) ans.pb('_');
		else ans.pb('X');
	}
	return ans;
}
