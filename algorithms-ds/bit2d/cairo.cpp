#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10;

int bit[maxn][maxn];

void upd(int x, int y, int v) {
	for(int i = x; i < maxn; i += i&-i)
		for(int j = y; j < maxn; j += j&-j)
			bit[i][j] = max(v, bit[i][j]);
}

int query(int x, int y) {
	int ans = 0;
	for(int i = x; i > 0; i -= i&-i)
		for(int j = y; j > 0; j -= j&-j)
			ans = max(ans, bit[i][j]);
	return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0; i < maxn; i++)
			for(int j = 0; j < maxn; j++)
				bit[i][j] = 0;
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int x, y; scanf("%d %d", &x, &y);
			ans = max(ans, query(x, y) + 1);
			upd(x, y, query(x, y) + 1);
		}
		printf("%d\n", ans);
	}
}