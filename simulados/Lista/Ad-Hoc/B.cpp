#include <cstdio>
#include <vector>
#include <utility>

constexpr int maxn = 1e5+10;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		std::vector<std::pair<int,int>> vec;
		std::vector<int> ans(m), lives(n+1, (m+1)>>1);
		bool ok = 1;
		for(int i = 0; i < m; i++) {
			int k; scanf("%d", &k);
			if(k == 1) {
				int v; scanf("%d", &v);
				ans[i] = v;
				if(--lives[v] < 0) ok = 0;
			} else {
				int a, b; scanf("%d %d", &a, &b);
				vec.push_back({a, b});
				k -= 2;
				while(k--) scanf("%d", &a); // trash
			}
		}
		for(int i = 0, ptr = 0; i < (int)vec.size(); i++) {
			while(ptr < m && ans[ptr]) ++ptr;
			ans[ptr] = lives[vec[i].first]?vec[i].first:vec[i].second;
			--lives[ans[ptr]];
		}
		if(!ok) { puts("NO"); continue; }
		puts("YES");
		for(int i = 0; i < m; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
}