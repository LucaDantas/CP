#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int mod = 1e9+7;
constexpr int maxn = 1e6+100;

int n;

struct SegmentTree {
	struct Matrix {
		int mat[4][4];
		
		void set(int a) {
			memset(mat, 0, sizeof mat);
			if(a == 1) {
				// 1 -> com os dois blocos pretos
				mat[0][0] = 1;
			} else if(a == 2) {
				// 2 -> com o bloco de cima preto
				mat[0][1] = mat[1][0] = 1;
			} else if(a == 3) {
				// 3 -> com o bloco de baixo preto
				mat[0][2] = mat[2][0] = 1;
			} else {
				// 4 -> com nada preto (tudo livre)
				mat[0][0] = mat[0][3] = mat[1][2] = mat[2][1] = mat[3][0] = 1;
			}
		}

		Matrix& operator*(Matrix a) {
			static Matrix c;
			memset(c.mat, 0, sizeof c.mat);
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					// Quero calcular a posição (i, j) da matriz
						for(int k = 0; k < 4; k++) {
							c.mat[i][j] += (int)(1ll * mat[i][k] * a.mat[k][j] % mod);
							if(c.mat[i][j] >= mod) c.mat[i][j] -= mod;
						}
				}
			}
			return c;
		}
	} tree[2*maxn];

	Matrix& idt() {
		static Matrix a; memset(a.mat, 0, sizeof a.mat);
		for(int i = 0; i < 4; i++) a.mat[i][i] = 1;
		return a;
	}

	void build() {
		for(int i = n-1; i > 0; i--)
			tree[i] = tree[i<<1|1] * tree[i<<1];
	}
	void upd(int p, int tipo) {
		for(tree[p += n].set(tipo); p > 0; p >>= 1) {
			int esq = p, dir = p^1;
			if(esq > dir) swap(esq, dir);
			tree[p>>1] = tree[dir] * tree[esq];
		}
	}
	// query the segment [l..r)
	Matrix query(int l, int r) {
		r++;
		Matrix esq = idt(), dir = idt();
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l&1) esq = tree[l++] * esq;
			if(r&1) dir = dir * tree[--r];
		}
		return dir*esq;
	}
} seg;

int v[2][maxn];

int tipo(int cima, int baixo) {
	return !cima + 2*(!baixo) + 1;
}

int main() {
	int q; scanf("%d %d", &n, &q);
	for(int i = n; i < 2*n; i++) seg.tree[i].set(4);
	seg.build();
	while(q--) {
		int t, i, j; scanf("%d %d %d", &t, &i, &j);
		i--, j--;
		if(t == 1) {
			v[i][j] = 1 - v[i][j];
			seg.upd(j, tipo(v[0][j], v[1][j]));
		} else {
			printf("%d\n", seg.query(i, j).mat[0][0]);
		}
	}
}
