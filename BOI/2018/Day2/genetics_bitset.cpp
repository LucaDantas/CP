#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1810;

string a[maxn];
bitset<maxn> b[maxn];

int dist(string x, string y) {
	int ans = 0;
	for(int i = 0; i < x.size(); i++)
		ans += x[i] != y[i];
	return ans;
}

int main() {
	int n, m, k; cin >> n >> m >> k;
	string s;
	for(int i = 0; i < n; i++) {
		cin >> s; a[i] = s;
		for(int i = 0; i < m; i++)
			s[i] = (s[i] == 'A') + '0';
		b[i] = bitset<maxn>(s);
	}

	for(int i = 0; i < n; i++) {
		bool ok = 1;
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			if(max(n, m) > 100) { if((b[i]^b[j]).count() != k) { ok = 0; break; } }
			else if(dist(a[i], a[j]) != k) { ok = 0; break; }
		}
		if(ok) printf("%d\n", i+1);
	}
}
