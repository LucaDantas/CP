#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10, inf = 0x3f3f3f3f;

int a[maxn], b[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	a[n+1] = -inf;
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	b[m+1] = inf;
	int ans = min(n, m);
	for(int i = 0; i <= min(n, m); i++) {
		int l = i, r = ans-1;
		while(l <= r) {
			int t = (l+r) >> 1;
			if(b[m-t+i] - a[i+1] <= 2*t)
				ans = t, r = t-1;
			else l = t+1;
		}
	}
	printf("%d\n", ans);
}