#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 2e5 + 10;

long long a[maxn];

long long gcd(int x, int y) { return !y ? x : gcd(x%y, x); }

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		for(int i = n-1; i > 0; i--)
			a[i] = abs(a[i] - a[i-1]);
		vector<pair<ll,int>> atual, prox;
		int ans = 1;
		for(int i = n-1; i > 0; i--) {
			prox.push_back({a[i], i});
			for(auto p : atual) {
				if(gcd(p.first, a[i]) == prox.back().first)
					prox.pop_back();
				prox.push_back({gcd(p.first, a[i]), p.second});
			}
			while(prox.size() && prox.back().first == 1)
				prox.pop_back();
			if(prox.size())
				ans = max(ans, prox.back().second - i + 2);
			atual = prox;
			prox.clear();
		}
		printf("%d\n", ans);
	}
}
