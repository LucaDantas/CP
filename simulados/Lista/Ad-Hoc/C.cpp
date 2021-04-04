#include <cstdio>
#include <set>
#include <utility>
#include <algorithm>
#include <vector>

std::set<std::pair<int,int>> st;
std::set<int> active;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		st.clear(); active.clear();
		int n; scanf("%d", &n);
		std::vector<int> val(n);
		if(n == 1) {
			int v; scanf("%d", &v);
			if(v == 1) puts("1 1");
			else puts("0");
			continue;
		}
		for(int i = 0; i < n; i++) {
			scanf("%d", &val[i]);
			if(i && std::__gcd(val[i], val[i-1]) == 1) st.insert({i-1, i});
			active.insert(i);
		}
		if(std::__gcd(val.back(), val[0]) == 1) st.insert({n-1, 0});
		std::vector<int> ans;
		std::vector<std::pair<int,int>> add;
		for(auto p = st.begin(); st.size() + add.size(); p = st.erase(p)) {
			if(p == st.end()) {
				for(auto x : add)
					st.insert(x);
				add.clear();
				p = st.begin();
			}
			auto next = [](int v) {
				auto it = active.upper_bound(v);
				if(it == active.end())
					return *active.begin();
				return *it;
			};
			auto prev = [](int v) {
				auto it = active.find(v);
				if(it == active.begin()) return *active.rbegin();
				return *(--it);
			};
			auto [a, b] = *p;
			if(!active.count(a) || !active.count(b)) continue;
			ans.push_back(b);
			active.erase(b);
			if(active.size() == 1) break;
			if(std::__gcd(val[a], val[next(a)]) == 1) add.push_back({a, next(a)});
			if(std::__gcd(val[prev(a)], val[a]) == 1) add.push_back({prev(a), a});
		}
		if(active.size() == 1 && val[*active.begin()] == 1) ans.push_back(*active.begin());
		printf("%ld", ans.size());
		for(int x : ans)
			printf(" %d", x+1);
		printf("\n");
	}
}