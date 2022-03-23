#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

vector<int> c[maxn][2];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int cor; scanf("%d", &cor);
			c[cor][0].push_back(i);
			c[cor][1].push_back(j);
		}
	}
	long long ans = 0;
	for(int i = 0; i < maxn; i++) {
		for(int k : {0, 1}) {
			sort(c[i][k].begin(), c[i][k].end(), greater<int>());
			int sz = (int)(c[i][k].size());
			for(int j = 0; j < sz; j++)
				ans += 1ll * c[i][k][j] * (sz-2*j-1);
		}
	}
	printf("%lld\n", ans);
}
