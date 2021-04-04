#include <cstdio>
#include <queue>

std::priority_queue<long long> q;

int main() {
	int n; scanf("%d", &n);
	long long d[n+1]{}, ans = 0;
	for(int i = 1; i <= n; i++) {
		int a, b; scanf("%d %d", &a, &b);
		d[i] = d[i-1] + a - b;
	}
	for(int i = 1; i <= n; i++) {
		if(d[i] < 0) ans -= d[i], d[i] = 0;
		else if(d[i] > d[n]) ans += d[i] - d[n], d[i] = d[n];
		q.push(d[i]);
		if(d[i] < q.top()) ans += q.top() - d[i], q.pop(), q.push(d[i]);
	}
	printf("%lld\n", ans);
}