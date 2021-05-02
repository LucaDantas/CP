#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int l[4*maxn], r[4*maxn], pai[4*maxn], atv[4*maxn];

vector<int> abre[4*maxn];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int L, R; scanf("%d %d", &L, &R);
		abre[L].push_back(R);
		atv[L]++;
		atv[R]--;
	}
	for(int i = 0, mx = 0; i < 4*n; i++) {
		atv[i+1] += atv[i];
		for(int x : abre[i])
			mx = max(mx, x);
		l[i] = mx + 1;
	}
	set<int> vivos; vivos.insert(4*n);
	pai[4*n] = -1;
	int mn = 4*n;
	for(int i = 4*n-2; i >= 0; i--) {
		r[i] = mn;
		auto it = vivos.lower_bound(l[i]);
		if(l[i] <= r[i] && it != vivos.end() && *it <= r[i])
			pai[i] = *it, vivos.insert(i);
		for(int x : abre[i])
			mn = min(mn, x);
	}
	if(!vivos.size() || *vivos.begin() > mn) return puts("-1"), 0;
	vector<int> ans;
	int pos = *vivos.begin();
	while(pai[pos] != -1) {
		if(atv[pos])
			ans.push_back(pos);
		pos = pai[pos];
	}
	printf("%ld\n", ans.size());
	for(int x : ans)
		printf("%d ", x);
	printf("\n");
}