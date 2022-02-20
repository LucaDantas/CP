#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

int pref[maxn];
int n, m;

struct Wire {
	int l, r, id;
	int sz() const { return r >= l ? r - l + 1 : r + (n - l + 1); }
	bool operator<(const Wire& o) const {
		if(l == o.l) return this->sz() > o.sz();
		return l < o.l;
	}
	bool inside(const Wire& o) const {
		int st = (l - o.l + n) % n;
		return st + this->sz() <= o.sz();
	}
} wr[maxn];

int pai[maxn];

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d %d", &wr[i].l, &wr[i].r); wr[i].id = i;
		if(wr[i].l <= wr[i].r) {
			pref[wr[i].l]++;
			pref[wr[i].r+1]--;
		} else {
			pref[wr[i].l]++;
			pref[1]++;
			pref[wr[i].r+1]--;
		}
	}

	for(int i = 1; i <= n; i++) {
		pref[i] += pref[i-1];
		pref[i+n] = pref[i];
		if(pref[i] < 2) return puts("impossible"), 0;
	}

	sort(wr, wr+m);

	int virou = 0;
	int fim = 0, aberto = -1;

	vector<Wire> brabos;

	memset(pai, -1, sizeof pai);
	Wire last = wr[0];
	for(int rep = 0; rep < 2; rep++) {
		for(int i = !rep; i < m; i++) {
			if(wr[i].inside(last) && wr[i].id != last.id) {
				if(rep) pai[wr[i].id] = last.id;
			} else {
				if(rep) brabos.push_back(wr[i]);
				last = wr[i];
			}
		}
	}

	vector<int> ans(m);

	auto print = [&]() {
		for(int i = 0; i < m; i++)
			printf("%d", ans[i]);
		puts("");
		exit(0);
	};

	if(brabos[0].sz() == n) {
		ans[brabos[0].id] = 1;
		print();
	}

	if(brabos.size() % 2 == 0) {
		for(int i = 0; i < brabos.size(); i++)
			ans[brabos[i].id] = i&1;
		
		for(int i = 0; i < m; i++)
			if(pai[i] != -1) ans[i] = 1^ans[pai[i]];

		print();
	}

	sort(brabos.begin(), brabos.end(), [](const Wire& a, const Wire& b) { return a.l < b.l; });

	for(int i = 0; i < brabos.size(); i++) {
		auto nxt = [&](int x) { return (x+1) % brabos.size(); };
		auto eu = brabos[i], prox = brabos[nxt(i)];
		int l = prox.l, r = eu.r;
		
		if(r < l) r += n;

		bool tem = 1;
		for(int j = l; j <= r; j++)
			tem &= pref[j] >= 3;

		auto no_intersection = [](Wire a, Wire b) {
			if(a.r < a.l) a.r += n;
			if(b.r < b.l) b.r += n;

			if(a.r < b.l) return 1;
			return 0;
		};
		if(tem || no_intersection(eu, prox)) {
			bool opa = 0;
			ans[ brabos[i].id ] = opa;

			for(int j = nxt(i); j != i; j = nxt(j)) {
				ans[ brabos[j].id ] = opa;
				opa ^= 1;
			}

			for(int i = 0; i < m; i++)
				if(pai[i] != -1) ans[i] = 1^ans[pai[i]];

			print();
		}
	}

	puts("impossible");
}
