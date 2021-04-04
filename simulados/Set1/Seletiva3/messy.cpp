#include "messy.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> p;
string s;

void add(int l, int r) {
	if(l == r) return;
	int m = (l+r) >> 1;
	for(int i = l; i <= m; i++) {
		s[i] = '1';
		add_element(s);
		s[i] = '0';
	}
	for(int i = l; i <= m; i++)
		s[i] = '1';
	add(m+1, r);
	for(int i = l; i <= r; i++)
		s[i] = s[i]=='1'?'0':'1'; // flip
	add(l, m);
	for(int i = m+1; i <= r; i++)
		s[i] = '0';
}

void solve(int l, int r, vector<int> b) {
	if(l == r) return (void)(p[l] = b[0]);

	vector<int> g1, g2;
	for(int x : b) {
		s[x] = '1';
		if(check_element(s)) g1.push_back(x);
		else g2.push_back(x);
		s[x] = '0';
	}

	int m = (l+r) >> 1;
	for(int x : g2)
		s[x] = '1';
	solve(l, m, g1);
	for(int x : g2)
		s[x] = '0';

	for(int x : g1)
		s[x] = '1';
	solve(m+1, r, g2);
	for(int x : g1)
		s[x] = '0';
}

vector<int> restore_permutation(int N, int w, int r) {
	n = N;
	p.resize(n);
	for(int i = 0; i < n; i++)
		s.push_back('0');
	add(0, n-1);
	compile_set();
	vector<int> b(n);
	iota(b.begin(), b.end(), 0);
	for(int i = 0; i < n; i++)
		s[i] = '0';
	solve(0, n-1, b);

	vector<int> ans(n);
	for(int i = 0; i < n; i++)
		ans[p[i]] = i;
	return ans;
}
