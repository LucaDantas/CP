#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		std::vector<int> a(n);
		std::map<int, int> cnt;
		std::vector<std::pair<int,int>> bad;
		bad.reserve(2*m);

		for(int& x : a)
			scanf("%d", &x), cnt[x]++;

		for(int i = 0, x, y; i < m; i++)
			scanf("%d %d", &x, &y), bad.emplace_back(x, y), bad.emplace_back(y, x);
		std::sort(bad.begin(), bad.end());

		std::vector<std::vector<int>> A(n+1);
		std::vector<int> tem;
		for(auto& [x, c] : cnt)
			A[c].push_back(x), tem.push_back(c);

		std::sort(tem.begin(), tem.end());
		tem.resize(std::unique(tem.begin(), tem.end()) - tem.begin());

		for(auto& x : A)
			std::reverse(x.begin(), x.end());

		long long ans = 0;

		for(int i = 0; i < (int)tem.size(); i++) {
			for(const int& x : A[tem[i]]) {
				for(int j = 0; j <= i; j++) {
					for(const int& y : A[tem[j]]) {
						if(x != y && !binary_search(bad.begin(), bad.end(), std::pair<int,int>(x, y))) {
							ans = std::max(ans, 1ll * (x+y) * (tem[i]+tem[j]));
							break;
						}
					}
				}
			}
		}

		printf("%lld\n", ans);
	}
}

