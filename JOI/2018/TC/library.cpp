#include <cstdio>
#include <vector>
#include <cassert>
#include<algorithm>
#include "library.h"
using namespace std;

#define pb push_back
#define sz(a) (int)((a).size())

vector<vector<int>> grp;

void Solve(int n)
{
	for(int i = 0; i < n; i++)
		grp.pb({i});

	while(sz(grp) > 1) {
		vector<vector<int>> dir, esq;
		vector<vector<int>> grande = grp;
		do {
			esq.clear();
			dir.clear();
			vector<int> qr(n);
			for(int i = 0; i < sz(grande)/2; i++)
				esq.pb(grande[i]);
			
			for(int i = sz(grande)/2; i < sz(grande); i++)
				dir.pb(grande[i]);

			for(auto x : esq)
				for(auto y : x)
					qr[y] = 1;

			if(Query(qr) < sz(esq)) grande = esq;
			else {
				fill(qr.begin(), qr.end(), 0);
				for(auto x : dir)
					for(auto y : x)
						qr[y] = 1;

				if(Query(qr) < sz(dir)) grande = dir;

				else {
					while(sz(esq) + sz(dir) > 2) {
						vector<vector<int>> l1, l2, r1, r2;
						
						for(int i = 0; i < sz(dir)/2; i++)
							r1.pb(dir[i]);
						
						for(int i = sz(dir)/2; i < sz(dir); i++)
							r2.pb(dir[i]);

						for(int i = 0; i < sz(esq)/2; i++)
							l1.pb(esq[i]);

						for(int i = sz(esq)/2; i < sz(esq); i++)
							l2.pb(esq[i]);
						

						fill(qr.begin(), qr.end(), 0);
						for(auto x : esq)
							for(auto y : x)
								qr[y] = 1;

						for(auto x : r1)
							for(auto y : x)
								qr[y] = 1;

						if(Query(qr) < sz(esq) + sz(r1)) dir = r1;
						else dir = r2;
						
						fill(qr.begin(), qr.end(), 0);
						for(auto x : l1)
							for(auto y : x)
								qr[y] = 1;
						
						for(auto x : dir)
							for(auto y : x)
								qr[y] = 1;

						if(Query(qr) < sz(l1) + sz(dir)) esq = l1;
						else esq = l2;
					}
				}
			}
		} while(sz(esq) + sz(dir) > 2);

		auto find = [&](vector<int>& achar) {
			for(int i = 0; i < sz(grp); i++) {
				if(grp[i].front() == achar.front()) return i;
				if(grp[i].front() == achar.back()) {reverse(grp[i].begin(), grp[i].end()); return i;}
			}
			assert(0);
			return -1;
		};

		auto apagar = [&](int pos) {
			swap(grp.back(), grp[pos]);
			grp.pop_back();
		};

		for(int cnt = 0; cnt < 2; cnt++, swap(esq[0], dir[0])) {
			vector<int> qr(n);
			qr[esq[0].back()] = 1;
			qr[dir[0].front()] = 1;
			if(Query(qr) == 2)
				reverse(dir[0].begin(), dir[0].end());
			else break;

			fill(qr.begin(), qr.end(), 0);
			qr[esq[0].back()] = 1;
			qr[dir[0].front()] = 1;
			if(Query(qr) == 2)
				reverse(esq[0].begin(), esq[0].end());
			else break;

			fill(qr.begin(), qr.end(), 0);
			qr[esq[0].back()] = 1;
			qr[dir[0].front()] = 1;
			if(Query(qr) == 2)
				reverse(dir[0].begin(), dir[0].end());
			else break;

			fill(qr.begin(), qr.end(), 0);
			qr[esq[0].back()] = 1;
			qr[dir[0].front()] = 1;
			if(Query(qr) == 1) break;
		}

		apagar(find(dir[0]));
		int id = find(esq[0]);
		for(auto add : dir[0])
			grp[id].pb(add);
	}

	for(int i = 0; i < n; i++)
		grp[0][i]++;
	printf("\n");
	Answer(grp[0]);
}
