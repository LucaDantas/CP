#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;

int main() {
	int t; scanf("%d", &t);
	int n; scanf("%d", &n);
	vector<int> x(n);
	for(int i = 0; i < n; i++)
		scanf("%d", &x[i]);
	sort(all(x));
	int ans = inf;
	for(int i = 1; i < n-1; i++)
		ans = min(ans, x[i+1] - x[i-1]);
	ans = min({ans, x[1] + x[0], 2*t-(x[n-1]+x[n-2])});
	if(ans&1)
		printf("%d.50\n", ans/2);
	else
		printf("%d.00\n", ans/2);
}
