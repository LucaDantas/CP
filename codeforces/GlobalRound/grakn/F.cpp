#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; scanf("%d", &n);
	vector<int> mark(n+1, -1);
	vector<pair<int,int>> ans;
	for(int rep = 0, start = 1; rep < 2; rep++, start = n - (1<<(31-__builtin_clz(n))) + 1) {
		int pot = (31-__builtin_clz(n));
		for(int p = 0; p <= pot; p++) {
			for(int i = start; i < start + (1<<pot) - (1<<p); i++) {
				if(mark[i] != p)
					ans.push_back({i, i+(1<<p)}), mark[i+(1<<p)] = p;
			}
		}
		mark.assign(n+1, -1);
	}
	printf("%d\n", (int)ans.size());
	for(auto it : ans)
		printf("%d %d\n", it.first, it.second);
}