#include "molecules.h"
#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pb push_back

vector<int> find_subset(int l, int u, vector<int> w) {
	int n = (int)(w.size());
	vector<int> ind(n);
	for(int i = 0; i < n; i++)
		ind[i] = i;
	sort(all(ind), [&](int a, int b){
		return w[a] < w[b];
	});
	sort(all(w));
	unsigned int pref = 0, suf = 0;
	int i = 0;
	vector<int> ans;
	for(; i <= n && pref <= u; i++) {
		if(suf >= l) {
			deque<int> extra;
			for(int pos = n-i; pos < n; pos++)
				extra.pb(pos);
			while(suf > u) {
				suf -= w[extra.back()];
				extra.pop_back();
				extra.push_front(n-1-i);
				suf += w[n-1-i];
				i++;
			}
			for(auto it : extra)
				ans.pb(ind[it]);
			break;
		}
		if(i < n)
			pref += w[i],
			suf += w[n-1-i];
	}
	return ans;
}
