#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())

using pii = pair<int, int>;

multiset<int> gaps;
set<int> s;

void add(int x) {
	auto it = s.insert(x).first;
	auto next_it = it;
	next_it++;

	if(next_it != s.end()) {
		gaps.insert(*next_it - x);
	}
	if(it != s.begin()) {
		auto prev_it = it;
		prev_it--;
		gaps.insert(x - *prev_it);

		if(next_it != s.end()) {
			gaps.erase(gaps.find(*next_it - *prev_it));
		}
	}
}

void remove(int x) {
	auto it = s.find(x), next_it = it;
	next_it++;
	if(next_it != s.end()) {
		gaps.erase(gaps.find(*next_it - *it));
	}
	if(it != s.begin()) {
		auto prev_it = it;
		prev_it--;
		gaps.erase(gaps.find(x - *prev_it));

		if(next_it != s.end()) {
			gaps.insert(*next_it - *prev_it);
		}
	}
	s.erase(x);
}

int query() {
	if(sz(s) <= 2) return 0;
	return *s.rbegin()-*s.begin()-*gaps.rbegin();
}

int main() {
	int n, q; scanf("%d %d", &n, &q);
	vector<int> p(n);
	for(auto& it : p)
		scanf("%d", &it);
	sort(all(p));

	s.insert(p[0]);
	for(int i = 1; i < n; i++) {
		gaps.insert(p[i] - p[i-1]);
		s.insert(p[i]);
	}	

	printf("%d\n", query());

	while(q--) {
		int t, x; scanf("%d %d", &t, &x);
		if(t)
			add(x);
		else
			remove(x);
		printf("%d\n", query());
	}
}