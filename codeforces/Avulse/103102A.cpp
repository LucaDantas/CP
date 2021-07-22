#include <cstdio>
#include <queue>

int main() {
	int n; scanf("%d", &n);
	std::priority_queue<long long> q;
	long long lazy = 0, ans = 0;
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);
		q.push(-lazy), q.push(-lazy);
		ans += q.top() + lazy, q.pop();
		lazy += a;
	}
	q.push(-lazy), q.push(-lazy);
	ans += q.top() + lazy, q.pop();
	printf("%lld\n", ans);
}

