#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

int t = 1;

vector<pair<int,long long>> val[maxn];
long long tot[maxn];

struct SegmentTree {
	struct Node {
		int cor, tempo;
		long long lazy; // cor == cor do itv, lazy == lazy do valor, tempo == tempo que aquele cara ganhou aquela cor
	} tree[4*maxn];
	void build() { for(int i = 1; i < 4*maxn; i++) tree[i].cor = 1, tree[i].tempo = 1; }
	void upd(int node, int i, int j, int l, int r, int c) { // mudo todo mundo desse intervalo pra essa cor e com esse tempo
		if(i > r || j < l) return;
		if(tree[node>>1].cor) tree[node].cor = tree[node>>1].cor;
		if(i >= l && j <= r && tree[node].cor) {
			tree[node].lazy += tot[tree[node].cor] -
				(--lower_bound(val[tree[node].cor].begin(), val[tree[node].cor].end(), pair<int,long long>(tree[node].tempo, 0)))->second;

			tree[node].cor = c, tree[node].tempo = t;
			return;
		}
		int m = (i+j) >> 1;
		upd(node<<1, i, m, l, r, c);
		upd(node<<1|1, m+1, j, l, r, c);
		tree[node].cor = 0; // com certeza algum dos filhos vai mudar e eu só coloco > 0 se for tudo a mesma operação
	}
	long long query(int node, int i, int j, int x) {
		if(tree[node>>1].cor) tree[node].cor = tree[node>>1].cor;
		if(i == j) return tree[node].lazy + tot[tree[node].cor] -
			(--lower_bound(val[tree[node].cor].begin(), val[tree[node].cor].end(), pair<int,long long>(tree[node].tempo, 0)))->second;
		int m = (i+j) >> 1;
		long long Val;
		if(x <= m) Val = query(node<<1, i, m, x);
		else Val = query(node<<1|1, m+1, j, x);
		return tree[node].lazy + Val;
	}
} seg;

int main() {
	int n, q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++)
		val[i].push_back({0, 0});
	seg.build();
	for(int i = 0; i < q; i++) {
		char s[10];
		scanf(" %s", s);
		if(strcmp(s, "Color") == 0) {
			int l, r, c; scanf("%d %d %d", &l, &r, &c);
			++t; seg.upd(1, 1, n, l, r, c);
		} else if(strcmp(s, "Add") == 0) {
			int c, v; scanf("%d %d", &c, &v);
			++t;
			tot[c] += v; val[c].push_back({t, tot[c]});
		} else {
			int id; scanf("%d", &id);
			printf("%lld\n", seg.query(1, 1, n, id));
		}
	}
}
