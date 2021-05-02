#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		vector<pair<int,int>> a(n);
		for(int i = 0; i < n; i++)
			scanf("%d %d", &a[i].first, &a[i].second), a[i].second = min(a[i].second, m);
		auto val = [](pair<int,int> x) { return 1ll * x.second - x.first; };
		sort(a.begin(), a.end(), [&](pair<int,int> x, pair<int,int> y) {
			if(val(x) >= 0 && val(y) >= 0) return x.first < y.first;
			if(val(x) >= 0) return true;
			if(val(y) >= 0) return false;
			return x.second > y.second;
		});
		long long vida = m;
		bool ok = 1;
		for(pair<int,int> x : a) {
			if(vida < x.first) ok = 0;
			vida += val(x);
		}
		puts(ok?"YES":"NO");
	}
}