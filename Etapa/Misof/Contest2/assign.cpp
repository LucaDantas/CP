#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

bool mark[maxn];
set<int> grp[maxn];
map<int,int> mp;

int w[maxn], a[maxn], d[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &w[i]), --w[i];
	
	for(int i = 0; i < n; i++)
		scanf("%d", &d[i]);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	
	for(int i = 0; i < n; i++)
		grp[w[i]].insert(a[i]), ++mp[w[i]];
	
	vector<pair<int,int>> v;
	for(auto x : mp) {
		int pos = x.first, val = x.second;
		if(x == *mp.rbegin())
			val -= (mp.begin()->first) + n - pos;
		else val -= (mp.upper_bound(pos)->first) - pos;
		v.push_back({val, pos});
	}

	pair<int,int> opt = {0x3f3f3f3f, 0};

	int now = 0;
	for(int rep = 0; rep < 2; rep++) {
		for(int i = 0; i < (int)(v.size()); i++) {
			opt = min(opt, {now, v[i].second});
			now += v[i].first;
		}
	}

	int ans = 0, start = opt.second;

	set<int> st;
	for(int i = start, foi = 0; i != start || !foi; i = (i+1)%n, foi = 1) {
		st.insert(grp[i].begin(), grp[i].end());
		
		auto it = st.upper_bound(d[i]);
		if(it != st.end()) ++ans;
		else it = st.begin();

		st.erase(it);
	}
	
	printf("%d\n", ans);
}