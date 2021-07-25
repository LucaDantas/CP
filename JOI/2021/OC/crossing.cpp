#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

char s[3][maxn], base[maxn];

int val[maxn];

int comb(array<int,3> a, array<int,3> b) { return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2])%3; }

vector<array<int,3>> bases = {{0, 0, 1}, {0, 1, 0}, {0, 2, 2}, {1, 0, 0}, {1, 1, 2}, {1, 2, 1}, {2, 0, 2}, {2, 1, 1}, {2, 2, 0}};

int tipo(char c) { return c == 'J' ? 0 : c == 'O' ? 1 : 2; }

int pot[] = {1, 3, 9};

int aceita(int msk, int fim) {
	array<int,3> aq = {msk%3, (msk/3)%3, (msk/9)%3};
	int eu = 0;
	for(int i = 0; i < 9; i++)
		if(comb(aq, bases[i]) == fim) eu |= 1<<i;
	return eu;
}

int cnt[27][3];

struct SegmentTree
{
	struct Node {
		int cor, qtd[27];
		Node& operator%(const Node& a) {
			static Node ret;
			if(cor == a.cor) ret.cor = cor;
			else ret.cor = -1;
			for(int i = 0; i < 27; i++)
				ret.qtd[i] = qtd[i] + a.qtd[i];
			return ret;
		}
		int operator+(const Node& a) {
			if(cor == a.cor) return cor;
			return -1;
		}
		void rmv() {
			for(int i = 0; i < 27; i++)
				cnt[i][cor] -= qtd[i];
		}
		void add() {
			for(int i = 0; i < 27; i++)
				cnt[i][cor] += qtd[i];
		}
	} tree[4*maxn];

	int a[maxn];

	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node].cor = a[i], tree[node].qtd[val[i]] = 1);
		int m = (i+j) >> 1;
		build(node<<1, i, m); build(node<<1|1, m+1, j);
		tree[node] = tree[node<<1] % tree[node<<1|1];
	}
	
	void upd(int node, int i, int j, int l, int r, int c) {
		if(i > r || j < l) return;
		if(i >= l && j <= r && tree[node].cor != -1) {
			if(c == tree[node].cor) return;
			tree[node].rmv();
			tree[node].cor = c;
			tree[node].add();
			return;
		}
		int m = (i+j) >> 1;
		if(tree[node].cor != -1)
			tree[node<<1|1].cor = tree[node<<1].cor = tree[node].cor;
		upd(node<<1, i, m, l, r, c);
		upd(node<<1|1, m+1, j, l, r, c);
		tree[node].cor = tree[node<<1] + tree[node<<1|1];
	}
} seg;

void check() {
	int pode = (1 << 10) - 1;
	for(int i = 0; i < 27 && pode; i++)
		for(int j = 0; j < 3; j++)
			if(cnt[i][j]) pode &= aceita(i, j);
	puts(pode ? "Yes" : "No");
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < 3; i++)
		scanf(" %s", s[i]);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 3; j++) {
			val[i] += tipo(s[j][i]) * pot[j];
		}
	}
	int q; scanf("%d", &q);
	scanf(" %s", base);
	for(int i = 0; i < n; i++)
		++cnt[val[i]][tipo(base[i])], seg.a[i] = tipo(base[i]);
	seg.build(1, 0, n-1);
	check();
	while(q--) {
		int l, r; char c; scanf("%d %d %c", &l, &r, &c);
		--l, --r;
		seg.upd(1, 0, n-1, l, r, tipo(c));
		check();
	}
}

