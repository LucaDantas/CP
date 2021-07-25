#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 3e5 + 10;

int n;

struct SegmentTree {
	int tree[2*maxn];
	void upd(int p, int v) {
		for(tree[p += n] = v; p > 0; p >>= 1)
			tree[p>>1] = max(tree[p], tree[p^1]);
	}
	// query the segment [l..r)
	int query(int l, int r) {
		++r;
		int ans = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l&1) ans = max(ans, tree[l++]);
			if(r&1) ans = max(ans, tree[--r]);
		}
		return ans;
	}
	void deb() {
		for(int i = 0; i < n; i++)
			cerr << tree[i+n] << ' ';
		cerr << endl;
	}
} seg;

int a[maxn];

vector<pii> td;

int main() {
	int D; scanf("%d %d", &n, &D);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]), td.push_back({a[i], -i});
	sort(td.begin(), td.end());
	for(int i = 0; i < n; i++)
		a[-td[i].second] = i;
	set<pii> vivos, vida;
	set<int> atv; int tempo = 0;
	auto limpa = [&](int l, int r) {
		auto it = atv.lower_bound(l);
		while(it != atv.end() && *it < r)
			seg.upd(*it, 0), it = atv.erase(it);
	};
	auto enche = [&](int pos) {
		auto it = vivos.lower_bound({pos, 0});
		while(it != vivos.end()) {
			vida.erase({it->second, it->first});
			it = vivos.erase(it);
		}
	};
	auto seca = [&]() {
		while(vida.size() && vida.begin()->first + D < tempo) {
			int l = vida.begin()->second;
			auto gld = vivos.lower_bound({l, inf});
			int r = gld == vivos.end() ? inf : gld->first;
			// db(l, r);
			limpa(l, r);
			vivos.erase({vida.begin()->second, vida.begin()->first});
			vida.erase(vida.begin());
		}
	};
	int ans = 0;
	for(int i = 0; i < n; i++) {
		enche(a[i]);
		vivos.insert({a[i], tempo});
		atv.insert(a[i]);
		vida.insert({tempo, a[i]});
		ans = max(ans, seg.query(0, a[i])+1);
		seg.upd(a[i], seg.query(0, a[i])+1);
		++tempo;
		seca();
	}
	printf("%d\n", ans);
}
