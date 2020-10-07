#include<bits/stdc++.h>
using namespace std;
#include "combo.h"

#define pb push_back
#define sz(a) (int)((a).size())

string guess_sequence(int N) {
	string p = "";
	vector<char> dif;
	if(press("AB")) {
		if(press("A")) p = "A";
		else p = "B";
	}
	else if(press("X")) p = "X";
	else p = "Y";
	if(N == 1) return p;
	for(char c : {'A','B','X','Y'})
		if(c != p[0])
			dif.pb(c);
	int last = 1;
	for(int i = 1; i < N-1; i++) {
		string q = "";
		q += p;
		q.pb(dif[1]);
		for(int j = 0; j < 3; j++) {
			q += p;
			q.pb(dif[0]);
			q.pb(dif[j]);
		}
		int ans = press(q);
		if(ans == sz(p)) p.pb(dif[2]);
		else if(ans == sz(p)+1) p.pb(dif[1]);
		else p.pb(dif[0]);
		assert(sz(p) - last == 1);
		last = sz(p);
	}
	for(int j = 0; j < 2; j++)
		if(press(p + dif[j]) == N) return p + dif[j];
	return p + dif[2];
}
