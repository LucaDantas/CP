#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back

set<pii> st; // posicao -> first, cor -> second

int main() {
	int n, q; scanf("%d %d", &n, &q);
	int ans = n;
	while(q--) {
		int l, r, k; scanf("%d %d %d", &l, &r, &k); k--;
		array<int,2> cnt; cnt[0] = cnt[1] = 0;
		auto it = st.lower_bound({l,-1});
		auto prev_it = it;
		int cor = st.size()==0||it == st.begin()||(*(--prev_it)).ss == 1?1:0;
		int last = l;
		vector<pii> rm;
		while(it != st.end() && (*it).ff <= r) {
			cnt[cor] += (*it).ff - last;
			cor = (*it).ss;
			rm.pb(*it);
			last = (*it).ff;
			++it;
		}
		cnt[cor] += r - last + 1;
		for(pii r : rm)
			st.erase(r);
		st.insert({l, k});
		if(r < n && !st.count({r+1, 0}) && !st.count({r+1, 1}))
			st.insert({r+1, cor});
		if(k) ans += cnt[0];
		else ans -= cnt[1];
		printf("%d\n", ans);
	}
}