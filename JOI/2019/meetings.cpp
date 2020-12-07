#include<bits/stdc++.h>
using namespace std;
#include "meetings.h"

#define pb push_back
#define sz(a) (a).size()

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

void solve(vector<int>& a) {
	shuffle(a.begin(), a.end(), rng);
	if(sz(a) <= 1) return;
	if(sz(a) == 2) return (void)(Bridge(min(a[0], a[1]), max(a[0], a[1])));
	int divide = Query(a[0], a[1], a[2]);
	vector<int> head, top;
	if(divide == a[0]) head.pb(a[1]);
	else head.pb(a[0]);
	vector<vector<int>> grp;
	map<int,int> id;
	id[head[0]] = 0;
	grp.pb({head[0]});
	top.pb({head[0]});
	set<int> seen;
	seen.insert(head[0]);
	for(int x : a) {
		if(x != divide) {
			bool ok = 0;
			for(int y : head) {
				if(x == top[id[y]]) {
					if(!seen.count(x)) {
						grp[id[y]].pb(x);
						seen.insert(x);
					}
					ok = 1;
					break;
				}
				if(!seen.count(x)) {
					int opa = Query(divide, x, top[id[y]]);
					if(opa == divide) continue;
					ok = 1;
					grp[id[y]].pb(x);
					top[id[y]] = opa;
					seen.insert(x);
					break;
				} else {ok = 1; break;}
			}
			if(!ok) id[x] = sz(head), head.pb(x), grp.pb({x}), top.pb({x}), seen.insert(x);
		}
	}
	for(int y : head) {
		Bridge(min(divide, top[id[y]]), max(divide, top[id[y]]));
		solve(grp[id[y]]);
	}
}

void Solve(int n) {
	vector<int> a;
	for(int i = 0; i < n; i++)
		a.pb(i);
	solve(a);
}
