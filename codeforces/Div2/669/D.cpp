#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10, inf = 0x3f3f3f3f;

int a[maxn], dp[maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	// 1 -> crescente, 2 -> decrescente
	stack<int> st1, st2;
	st1.push(n);
	st2.push(n);
	for(int i = n-1; i >= 1; i--) {
		int &best = dp[i]; best = inf;

		// stack 1
		while(st1.size() && a[i] > a[st1.top()]) {
			best = min(best, dp[st1.top()]+1);
			st1.pop();
		}
		if(st1.size()) best = min(best, dp[st1.top()]+1);
		if(st1.size() && a[i] == a[st1.top()]) st1.pop();
		st1.push(i);

		// stack 2
		while(st2.size() && a[i] < a[st2.top()]) {
			best = min(best, dp[st2.top()]+1);
			st2.pop();
		}
		if(st2.size()) best = min(best, dp[st2.top()]+1);
		if(st2.size() && a[i] == a[st2.top()]) st2.pop();
		st2.push(i);
	}
	printf("%d\n", dp[1]);
}