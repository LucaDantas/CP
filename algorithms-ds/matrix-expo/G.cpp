#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int mul(int a, int b) {
	return (int)(1ll * a * b % mod);
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

struct Matrix
{
	vector<vector<int>> mat;

	Matrix(int n) : mat(n, vector<int>(n)) {}

	Matrix(int n, int m) : mat(n, vector<int>(m)) {}

	Matrix() {}

	Matrix& operator*(const Matrix& a) {
		int n = sz(mat);

		static Matrix c;
		c.mat.assign(n, vector<int>(n));
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					add_self(c.mat[i][j], mul(mat[i][k], a.mat[k][j]));

		return c;
	}

	friend ostream& operator<<(ostream &os, const Matrix& v) { 
		int n = sz(v.mat), m = sz(v.mat[0]);
		for(int i = 0; i < n; i++) {
			os << '['; string sep = "";
			for(int j = 0; j < m; j++) {
				os << sep << v.mat[i][j], sep = ", ";
			}
			os << "]\n";
		}
		return os;
	}
};

Matrix power(Matrix b, long long e) {
	int n = sz(b.mat);
	Matrix ans(n);
	rep(i,0,n) ans.mat[i][i] = 1;

	while(e) {
		if(e&1)
			ans = ans * b;
		b = b * b;
		e >>= 1;
	}

	return ans;
}

Matrix multiplicar(Matrix a, Matrix b) { // multiplica quadrado com linha
	int n = sz(a.mat);
	Matrix ans(n, 1);

	rep(i,0,n)
		rep(k,0,n)
			add_self(ans.mat[i][0], mul(a.mat[i][k], b.mat[k][0]));

	return ans;
}

int main() {
	int n; ll k; scanf("%d %lld", &n, &k);
	Matrix a(n+3), b(n+3, 1);
	
	rep(i,0,n) scanf("%d", &b.mat[i][0]);
	if(k < n) {printf("%d\n", b.mat[k][0]); return 0;}

	reverse(b.mat.begin(), b.mat.begin()+n);

	b.mat[n][0] = 1;
	b.mat[n+1][0] = n;
	b.mat[n+2][0] = n*n;
	
	rep(i,0,n+3) scanf("%d", &a.mat[0][i]);

	rep(i,1,n) a.mat[i][i-1] = 1;

	a.mat[n][n] = 1;
	a.mat[n+1][n] = a.mat[n+1][n+1] = 1;
	a.mat[n+2][n+2] = a.mat[n+2][n] = 1;
	a.mat[n+2][n+1] = 2;

	printf("%d\n", multiplicar(power(a, k-n+1), b).mat[0][0]);
}
