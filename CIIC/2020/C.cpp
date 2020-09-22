#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int mod = 1e9+7;
constexpr int maxn = 1e6+10;

struct SegmentTree {
	struct Matrix {
		int mat[4][4];
		
		Matrix(){ memset(mat, 0, sizeof mat); }
		
		Matrix(int a) {
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
		
//		friend ostream& operator<<(ostream& os, Matrix a) {
//			for(int i = 0; i < 4; i++) {
//				os << "[";
//				for(int j = 0; j < 4; j++) {
//					os << ' ' << a.mat[i][j];
//				}
//				os << " ]\n";
//			}
//			return os << "\n";
//		}
	} tree[4*maxn];

	Matrix idt() {
		Matrix a;
		for(int i = 0; i < 4; i++) a.mat[i][i] = 1;
		return a;
	}

	// Agora as coisas da seg
	void build(int node, int i, int j) {
		if(i == j) {
			tree[node].set(4);
		} else {
			int m = (i+j) >> 1;
			build(2*node, i, m); build(2*node+1, m+1, j);
			tree[node] = tree[2*node+1] * tree[2*node];
		}
	}

	void upd(int node, int i, int j, int pos, int tipo) {
		if(i == j) {
			tree[node].set(tipo);
		} else {
			int m = (i+j) >> 1;
			if(pos <= m) upd(2*node, i, m, pos, tipo);
			else upd(2*node+1, m+1, j, pos, tipo);
			tree[node] = tree[2*node+1] * tree[2*node];
		}
	}

	Matrix query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return idt();
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return query(2*node+1, m+1, j, l, r) * query(2*node, i, m, l, r);
	}
} seg;

int v[2][maxn];

int tipo(int cima, int baixo) {
	return !cima + 2*(!baixo) + 1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
//	int n, q; scanf("%d %d", &n, &q);
	int n, q; cin >> n >> q;
	seg.build(1, 1, n);
	while(q--) {
//		int t, i, j; scanf("%d %d %d", &t, &i, &j);
		int t, i, j; cin >> t >> i >> j;
		if(t == 1) {
			v[i-1][j] = 1 - v[i-1][j];
			seg.upd(1, 1, n, j, tipo(v[0][j], v[1][j]));
		} else {
			cout << seg.query(1, 1, n, i, j).mat[0][0] << '\n';
//			printf("%d\n", seg.query(1, 1, n, i, j).mat[0][0]);
		}
	}
}
