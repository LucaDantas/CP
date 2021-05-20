#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e5+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll a[maxn], b[maxn];

// void db(priority_queue<ll, vector<ll>, greater<ll>> q) {
// 	while(q.size()) printf("%lld ", q.top()), q.pop();
// 	printf("\n");
// }

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);

	priority_queue<ll, vector<ll>, greater<ll>> dif;
	ll ans = a[1];
	for(int i = 2; i <= n; i++) {
		if(i&1) {
			if(dif.size() && dif.top() + b[i] <= a[i]) {
				ans += dif.top() + b[i];
				dif.pop(), dif.push(a[i] - b[i]);
			}
			else ans += a[i];
		}
		else {
			ans += b[i];
			dif.push(a[i] - b[i]);
		}
	}
	printf("%lld\n", ans);
}