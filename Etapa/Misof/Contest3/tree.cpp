#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10, inf = 0x3f3f3f3f;

int x[maxn], h[maxn];

int l[maxn], r[maxn]; // qual o primeiro momento que eu consigo cair pra esquerda->l e direita->r

struct BIT {
	int bit[maxn];
	void upd(int x, int v) {
		for(x++; x < maxn; x += x&-x)
			bit[x] += v;
	}
	int query(int x) {
		int ans = 0;
		for(x++; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
} bit;

vector<pair<int,int>> query[maxn]; // posicao no vetor == l, .first == r, .second == id
vector<pair<int,int>> ev[maxn]; // add element to bit

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", x+i, h+i);

	for(int i = 1; i <= n; i++) {
		if(x[i] - x[1] < h[i]) { l[i] = 0; continue; }
		l[i] = i;
		while(l[i] >= 1 && x[i] - x[l[i]] < h[i]) {
			if(x[i] - x[l[i]] >= h[l[i]])
				--l[i];
			else 
				l[i] = l[l[i]]-1;
		}
		l[i]++; // com esse negocio acima eu chego no primeiro cara que todo mundo antes caiu
	}

	for(int i = n; i >= 1; i--) {
		if(x[n] - x[i] < h[i]) { r[i] = n+1; continue; }
		r[i] = i;
		while(r[i] <= n && x[r[i]] - x[i] < h[i]) {
			if(x[r[i]] - x[i] >= h[r[i]])
				++r[i];
			else
				r[i] = r[r[i]]+1;
		}
		--r[i];
	}

	for(int i = 1; i <= n; i++) {
		ev[l[i]].push_back({i, 1});
		ev[i].push_back({r[i], 1});
		ev[l[i]].push_back({r[i],-1});
	}

	for(int i = 0; i < q; i++) {
		int l, r; scanf("%d %d", &l, &r);
		query[l].push_back({r, i});
	}

	vector<int> ans(q);

	for(int i = n; i >= 1; i--) {
		for(pair<int,int> p : ev[i])
			bit.upd(p.first, p.second);
		for(pair<int,int> p : query[i])
			ans[p.second] = bit.query(p.first);
	}

	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
