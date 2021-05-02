#include <cstdio>
#include <cstring>

constexpr int maxn = 101, mod = 1000000007;

inline void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

template <int N>
struct Matrix
{
	int a[N][N];
	Matrix& operator*(const Matrix& o) {
		static Matrix<N> ans;
		memset(ans.a, 0, sizeof ans.a);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				for(int k = 0; k < N; k++)
					add(ans.a[i][j], (int)(1ll * a[i][k] * o.a[k][j] % mod));
		return ans;
	}
	// Exponentiation in place
	void power(int e) {
		static Matrix<N> ans;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				ans.a[i][j] = a[i][j], a[i][j] = i == j;
		while(e) {
			if(e&1) *this = ans * (*this);
			ans = ans * ans;
			e >>= 1;
		}
	}
	void manda() {
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				printf("%d%c", a[i][j], " \n"[j==N-1]); 
	}
};

int power(int b, int e) {
	int ans = 1;
	while(e) {
		if(e&1) ans = (int)(1ll * ans * b % mod);
		b = (int)(1ll * b * b % mod);
		e >>= 1;
	}
	return ans;
}

int a[maxn];
Matrix<maxn> base;

int main() {
	int n, m, k; scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < n; i++)
		scanf("%d", a+i);
	for(int i = 0, x, y; i < m; i++) {
		scanf("%d %d", &x, &y); --x, --y;
		add(base.a[x][y], (mod+1)>>1);
		add(base.a[y][x], (mod+1)>>1);
		add(base.a[x][x], (mod+1)>>1);
		add(base.a[y][y], (mod+1)>>1);
		for(int j = 0; j < n; j++)
			if(j != x && j != y)
				++base.a[j][j];
	}
	int divM = power(m, mod-2);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			base.a[i][j] = (int)(1ll * base.a[i][j] * divM % mod);
	base.power(k);

	for(int i = 0; i < n; i++) {
		int ans = 0;
		for(int j = 0; j < n; j++)
			add(ans, (int)(1ll * a[j] * base.a[i][j] % mod));
		printf("%d\n", ans);
	}
}