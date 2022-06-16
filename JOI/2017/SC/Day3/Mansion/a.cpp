#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

int l[maxn], r[maxn];

int edge_sweep_l[maxn], edge_sweep_r[maxn];

vector<int> keys[maxn];

bool tem(int x, int y, int cor) {
	// return 1 if there is some element with color 'cor' inside the open interval ]x, y[
	auto it = upper_bound(keys[cor].begin(), keys[cor].end(), x);
	return it != keys[cor].end() && *it < y;
}

struct MP {
	vector<pair<int,int>> mp;
	void add(int i, int val) {
		while(mp.size() && mp.back().second >= val)
			mp.pop_back();
		mp.push_back({i, val});
	}
	int query(int x) { return (--lower_bound(mp.rbegin(), mp.rend(), pair<int,int>(x, -1)))->second; }
} mp;

int main() {
	int n; scanf("%d", &n);

	for(int i = 1; i < n; i++) {
		int c; scanf("%d", &c);
		edge_sweep_l[i] = edge_sweep_r[i+1] = c;
	}

	for(int i = 1; i <= n; i++) {
		int a, b; scanf("%d", &b);
		while(b--) {
			scanf("%d", &a);
			keys[a].push_back(i);
		}
	}

	// for(i = {0, n-1}) -> defino l[i]
	// for(i = {n-1, 0}) -> defino r[i] usando l[i], e também redefino l[i] overextending it
	
	l[1] = 0, r[n] = n+1; // the color of the edges are defined from [1, n] so we'll never be able to open c[0] and c[n+1] since they're 0
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		l[i] = i-1;
		while(tem(l[i], i+1, edge_sweep_l[l[i]]))
			l[i] = l[l[i]];
	}

	for(int i = n; i >= 1; i--) {
		r[i] = i+1;
		bool foi = 1;
		while(foi) {
			foi = 0;
			while(tem(l[i], r[i], edge_sweep_r[r[i]]))
				r[i] = r[r[i]], foi = 1;

			if(r[i] - i > 1)
				l[i] = min(l[i], mp.query(r[i]));
			while(tem(l[i], r[i], edge_sweep_l[l[i]]))
				l[i] = l[l[i]];
		}
		mp.add(i, l[i]);
	}

	int q; scanf("%d", &q);
	while(q--) {
		int x, y; scanf("%d %d", &x, &y);
		puts(y > l[x] && y < r[x] ? "YES" : "NO");
	}
}
