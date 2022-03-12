#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

bool mark[maxn];
set<int> grp[maxn];
map<int,int> mp;

int w[maxn], a[maxn], d[maxn];

int pref[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &w[i]), --w[i], pref[w[i]]++;

	pref[0]--;
	for(int i = 1; i < n; i++)
		pref[i] += pref[i-1]-1;

	for(int i = 0; i < n; i++)
		scanf("%d", &d[i]);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	
	for(int i = 0; i < n; i++)
		grp[w[i]].insert(a[i]);

	int ans = 0, start = (min_element(pref, pref+n)-pref+1)%n;

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
