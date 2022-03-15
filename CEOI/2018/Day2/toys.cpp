#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int f[maxn];

void sieve() {
	for(int i = 0; i < maxn; i++) {
		if(!f[i]) {
			f[i] = i;
			for(int j = i*i; j < maxn; j += i)
				f[i] = i;
		}
	}
}

vector<int> dv(int x) {
	vector<int> ans;
	for(int i = 2; i*i <= x; i++)
		if(x % i == 0) ans.push_back(i), ans.push_back(x / i);
	if(ans.size() >= 2 && ans[ans.size() - 2] * ans[ans.size() - 2] == x)
		ans.pop_back();
	ans.push_back(x);
	sort(ans.begin(), ans.end(), greater<int>());
	return ans;
}

set<int> mark;

void brute(int val, int soma, vector<int> d2) {
	if(val == 1) return (void)(mark.insert(soma));
	vector<int> d;
	while(d2.size()) {
		if(val % d2.back() == 0) d.push_back(d2.back());
		d2.pop_back();
	}
	while(d.size()) {
		brute(val / d.back(), soma + d.back() - 1, d);
		d.pop_back();
	}
}

int main() {
	int n; scanf("%d", &n);
	brute(n, 0, dv(n));
	printf("%ld\n", mark.size());
	for(int x : mark)
		printf("%d ", x);
	puts("");
}
