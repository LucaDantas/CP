#include<cstdio>
#include<queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> q;

int main() {
	int n; scanf("%d", &n);
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		int p; scanf("%d", &p);
		if(q.size() && q.top() < p) ans += p - q.top(), q.pop(), q.push(p), q.push(p);
		else q.push(p);
	}
	printf("%lld\n", ans);
}
