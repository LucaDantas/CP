#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e6+10, maxlog = 21;

int cnt[maxlog+1], erradas[maxlog+1], tam[maxlog], a[maxn], n, q, k;

set<int> pos[maxlog+1];

bool check() {
	int mx = 0;
	for(int i = maxlog; i >= 1; i--) {
		if(erradas[i] || cnt[i] > 1) return 0;
		if(cnt[i]) {mx = *pos[i].begin(); break;}
	}
	for(int i = 1; i < maxlog; i++) {
		if(erradas[i]) return 0;
	}
	int esq = mx - 1, dir = n - mx, opa = 0;
	while(esq || dir) {
		if((esq+1)/2 + (dir+1)/2 != cnt[++opa]) return 0;
		esq >>= 1, dir >>= 1;
	}

	for(int p = mx+1, i = 1; p <= n; p += tam[i-1], i++)
		if(a[p] != i) return 0;

	for(int p = mx-1, i = 1; p >= 1; p -= tam[i-1], i++)
		if(a[p] != i) return 0;
	return 1;
}

int main() {
	scanf("%d %d %d", &n, &q, &k);
	if(k) return 0;
	for(int i = 1; i <= n; i++) {
		int v; scanf("%d", &v);
		v = min(v, maxlog);
		a[i] = v;
		++cnt[v];
		pos[v].insert(i);
	}
	tam[0] = 1;
	for(int i = 1; i < maxlog; i++) {
		tam[i] = tam[i-1]*2;
		if(cnt[i]) {
			int last = 0;
			for(int x : pos[i]) {
				if(last && x - last != tam[i])
					++erradas[i];
				last = x;
			}
		}
	}
	printf("%d\n", check());
	while(q--) {
		int i, c; scanf("%d %d", &i, &c);
		c = min(c, maxlog);

		--cnt[a[i]];
		auto it = pos[a[i]].find(i);
		if(it != pos[a[i]].begin() && ((*it) - (*prev(it))) != tam[a[i]])
			--erradas[a[i]];
		if(next(it) != pos[a[i]].end() && ((*next(it)) - (*it)) != tam[a[i]])
			--erradas[a[i]];
		if(it != pos[a[i]].begin() && next(it) != pos[a[i]].end() && ((*next(it)) - (*prev(it))) != tam[a[i]])
			++erradas[a[i]];
		pos[a[i]].erase(it);

		it = pos[c].upper_bound(i);
		++cnt[c];
		if(it != pos[c].end() && ((*it) - i) != tam[c])
			++erradas[c];
		if(it != pos[c].begin() && (i - (*prev(it))) != tam[c])
			++erradas[c];
		if(it != pos[c].end() && it != pos[c].begin() && ((*it) - (*prev(it))) != tam[c])
			--erradas[c];

		pos[c].insert(i);
		a[i] = c;

		printf("%d\n", check());
	}
}