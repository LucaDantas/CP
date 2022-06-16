#include "park.h"
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

int rnd(int x) { return (rng() % x + x) % x; }

constexpr int maxn = 1410;

int ask[maxn];

int Ask2(int a, int b, int c[]) { if(a > b) swap(a, b); return Ask(a, b, c); }
void Answer2(int a, int b) { if(a > b) swap(a, b); Answer(a, b); }

int edge(int a, int b) {
	// ask if there is a direct edge between a and b
	memset(ask, 0, sizeof ask);
	ask[a] = ask[b] = 1;
	return Ask2(a, b, ask);
}

vector<vector<int>> group(int a, vector<int> subtrees, vector<int> tot) {
	// we know there is an edge between a and b
	
	vector<vector<int>> ans;

	vector<bool> mark(tot.size());

	shuffle(subtrees.begin(), subtrees.end(), rng);

	int n = (int)(tot.size());
	for(int i = 0; i < n; i++) {
		mark[i] = tot[i] == a;
		for(int b : subtrees)
			mark[i] = mark[i] || (tot[i] == b);
	}

	for(int b : subtrees) {
		ans.push_back({b});
		if(b == subtrees.back()) continue;
		for(int i = 0; i < n; i++) {
			if(mark[i]) continue;

			memset(ask, 0, sizeof ask);
			for(int j = 0; j < n; j++)
				ask[tot[j]] = 1;
			ask[b] = 0;

			if(!Ask2(a, tot[i], ask)) {
				ans.back().push_back(tot[i]);
				mark[i] = 1;
			}
		}
	}

	for(int i = 0; i < n; i++)
		if(!mark[i]) ans.back().push_back(tot[i]);

	return ans;
}

vector<int> find_neighbours(int a, vector<int> possible) {
	vector<int> ans;
	for(int b : possible)
		if(b != a && edge(a, b)) ans.push_back(b);
	return ans;
}

void go(vector<int> possible, int depth) {
	if(possible.size() <= 1) return;
	if(possible.size() == 2) {
		Answer2(possible[0], possible[1]);
		return;
	}
	int a = possible[0];
	vector<int> neighbours = find_neighbours(a, possible);
	for(int b : neighbours)
		Answer2(a, b);

	vector<vector<int>> grp = group(a, neighbours, possible);

	for(vector<int> sub : grp)
		go(sub, depth+1);
}

namespace old {
	vector<vector<int>> group(int a, vector<int> subtrees, vector<int> tot) {
	// we know there is an edge between a and b
	
	vector<vector<int>> ans;
 
	vector<bool> mark(tot.size());
 
	shuffle(subtrees.begin(), subtrees.end(), rng);
 
	int n = (int)(tot.size());
	for(int i = 0; i < n; i++) {
		mark[i] = tot[i] == a;
		for(int b : subtrees)
			mark[i] = mark[i] || (tot[i] == b);
	}
 
	for(int b : subtrees) {
		ans.push_back({b});
		for(int i = 0; i < n; i++) {
			if(mark[i]) continue;
 
			memset(ask, 0, sizeof ask);
			for(int j = 0; j < n; j++)
				ask[tot[j]] = 1;
			ask[b] = 0;
 
			if(!Ask2(a, tot[i], ask)) {
				ans.back().push_back(tot[i]);
				mark[i] = 1;
			}
		}
	}
 
	return ans;
}
 
vector<int> find_neighbours(int a, vector<int> possible) {
	vector<int> ans;
	for(int b : possible)
		if(b != a && edge(a, b)) ans.push_back(b);
	return ans;
}
 
void go(vector<int> possible) {
	if(possible.size() <= 1) return;
	if(possible.size() == 2) {
		Answer2(possible[0], possible[1]);
		return;
	}
	shuffle(possible.begin(), possible.end(), rng);
	int a = possible[rnd(possible.size())];
	vector<int> neighbours = find_neighbours(a, possible);
	for(int b : neighbours)
		Answer2(a, b);
 
	vector<vector<int>> grp = group(a, neighbours, possible);
 
	for(vector<int> sub : grp)
		go(sub);
}
}

void Detect(int T, int N) {
	if(T == 1) {
		for(int i = 0; i < N; i++)
			for(int j = i+1; j < N; j++)
				if(edge(i, j)) Answer2(i, j);
		return;
	}
	vector<int> all(N);
	iota(all.begin(), all.end(), 0);
	if(T == 2) return (void)(old::go(all));
	go(all, 0);
}
